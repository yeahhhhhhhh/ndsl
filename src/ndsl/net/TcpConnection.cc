/**
 * @file TcpConnection.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/Log.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/utils/Log.h"
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstdio>

namespace ndsl {
namespace net {

TcpConnection::TcpConnection()
    : pTcpAcceptor_(NULL)
    , pTcpChannel_(NULL)
{}

TcpConnection::TcpConnection(TcpAcceptor *tcpAcceptor)
    : pTcpAcceptor_(tcpAcceptor)
    , pTcpChannel_(NULL)
{}

TcpConnection::~TcpConnection() {}

int TcpConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->setCallBack(handleRead, handleWrite, this);
    return pTcpChannel_->enroll(true);
}

int TcpConnection::onSend(
    void *buf,
    ssize_t len,
    int flags,
    Callback cb,
    void *param)
{
    // 当创建顺序不对的时候 这里容易报段错误 故 加一条输出
    if (NULL == pTcpChannel_) {
        // TODO:
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPCONNECTION, "pTcpChannel == NULL\n");
        return S_FALSE;
    } else {
        int sockfd = pTcpChannel_->getFd();

        // 加上MSG_NOSIGNAL参数 防止send失败向系统发送消息导致关闭
        ssize_t n = send(sockfd, buf, len, flags | MSG_NOSIGNAL);
        if (n == len) {
            // 写完 通知用户
            // LOG(LOG_INFO_LEVEL,
            //     LOG_SOURCE_TCPCONNECTION,
            //     "TcpConnection::onSend write complete\n");
            if (cb != NULL) cb(param);
            // 释放掉buf占用的空间 TODO: 暂时注释
            // if (buf != NULL) free(buf);
            return S_OK;
        } else if (n < 0) {
            // 出错 通知用户
            LOG(LOG_ERROR_LEVEL,
                LOG_SOURCE_TCPCONNECTION,
                "TcpConnection::onSend send error\n");
            errorHandle_(errno, pTcpChannel_->getFd());
            // 释放掉buf占用的空间 TODO: 暂时注释
            // if (buf != NULL) free(buf);
            return S_FALSE;
        }

        LOG(LOG_INFO_LEVEL,
            LOG_SOURCE_TCPCONNECTION,
            "TcpConnection::onSend send for next time\n");
        pInfo tsi = new Info;
        tsi->offset_ = n;
        tsi->sendBuf_ = (void *) buf;
        tsi->readBuf_ = NULL;

        // TODO: memory leak
        tsi->len_ = new ssize_t;
        (*tsi->len_) = len;

        tsi->flags_ = flags | MSG_NOSIGNAL;
        tsi->cb_ = cb;
        tsi->param_ = param;

        qSendInfo_.push(tsi);

        return S_OK;
    }
}

int TcpConnection::handleWrite(void *pthis)
{
    TcpConnection *pThis = static_cast<TcpConnection *>(pthis);
    int sockfd = pThis->pTcpChannel_->getFd();

    if (sockfd < 0) { return -1; }
    ssize_t n;

    // 有数据待写
    if (pThis->qSendInfo_.size() > 0) {
        pInfo tsi = pThis->qSendInfo_.front();

        if ((n = send(
                 sockfd,
                 (char *) tsi->sendBuf_ + tsi->offset_,
                 (*tsi->len_) - tsi->offset_,
                 tsi->flags_)) > 0) {
            tsi->offset_ += n;

            if (tsi->offset_ == (*tsi->len_)) {
                if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
                pThis->qSendInfo_.pop();
                // 释放掉buf占用的空间 TODO: 暂时注释
                // if (tsi->sendBuf_ != NULL) free(tsi->sendBuf_);
                delete tsi; // 删除申请的内存
            } else if (n == 0) {
                // 发送缓冲区满 等待下一次被调用
                LOG(LOG_INFO_LEVEL,
                    LOG_SOURCE_TCPCONNECTION,
                    "send error wait next time send\n");
                return S_OK;
            }
        } else if (n < 0) {
            // 写过程中出错 出错之后处理不了 注销事件 并交给用户处理
            LOG(LOG_INFO_LEVEL,
                LOG_SOURCE_TCPCONNECTION,
                "send error can not deal\n");
            pThis->errorHandle_(errno, pThis->pTcpChannel_->getFd());

            // 将事件从队列中移除
            pThis->qSendInfo_.pop();

            // 释放掉buf占用的空间 TODO: 暂时注释
            // if (tsi->sendBuf_ != NULL) free(tsi->sendBuf_);
            delete tsi;

            return S_FALSE;
        }
    }
    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FALSE，并设置 errno
// 的值。
// 相当于注册一个回调函数
int TcpConnection::onRecv(
    char *buf,
    ssize_t *len,
    int flags,
    Callback cb,
    void *param)
{
    // 作为下面recv接收的临时量，直接用(*len)接收会变成2^64-1 不知道为什么
    // 答案1：是flag参数的问题
    ssize_t n;

    int sockfd = pTcpChannel_->getFd();
    if ((n = recv(sockfd, buf, MAXLINE, flags | MSG_NOSIGNAL)) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            LOG(LOG_INFO_LEVEL,
                LOG_SOURCE_TCPCONNECTION,
                "TcpConnection::onRecv EAGAIN\n");

            // 保存用户信息
            RecvInfo_.readBuf_ = buf;
            RecvInfo_.sendBuf_ = NULL;
            RecvInfo_.flags_ = flags | MSG_NOSIGNAL;
            RecvInfo_.len_ = len;
            RecvInfo_.cb_ = cb;
            RecvInfo_.param_ = param;

            return S_OK;
        } else {
            // 出错 回调用户
            LOG(LOG_INFO_LEVEL,
                LOG_SOURCE_TCPCONNECTION,
                "TcpConnection::onRecv recv error can not deal\n");
            errorHandle_(errno, pTcpChannel_->getFd());
            return S_FALSE;
        }
    }
    (*len) = n;

    LOG(LOG_INFO_LEVEL,
        LOG_SOURCE_TCPCONNECTION,
        "TcpConnection::onRecv recv complete\n");

    // 一次性读完之后通知用户
    if (cb != NULL) cb(param);
    return S_OK;
}

int TcpConnection::handleRead(void *pthis)
{
    // printf("TcpConnection::handleRead\n");

    TcpConnection *pThis = static_cast<TcpConnection *>(pthis);
    int sockfd = pThis->pTcpChannel_->getFd();
    if (sockfd < 0) { return S_FALSE; }

    ssize_t n;
    if ((n = recv(
             sockfd,
             pThis->RecvInfo_.readBuf_,
             MAXLINE,
             pThis->RecvInfo_.flags_)) < 0) {
        // 出错
        pThis->errorHandle_(errno, pThis->pTcpChannel_->getFd());
        (*pThis->RecvInfo_.len_) = n;
        return S_FALSE;
    }

    (*pThis->RecvInfo_.len_) = n;

    // 完成数据读取之后通知mul
    if (pThis->RecvInfo_.cb_ != NULL)
        pThis->RecvInfo_.cb_(pThis->RecvInfo_.param_);

    return S_OK;
}

int TcpConnection::onAccept(
    TcpConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    return pTcpAcceptor_->setInfo(pCon, addr, addrlen, cb, param);
}

int TcpConnection::sendMsg(
    struct msghdr *msg,
    int flags,
    Callback cb,
    void *param)
{
    int sockfd = pTcpChannel_->getFd();
    ssize_t len = sizeof(struct msghdr);

    // 加上MSG_NOSIGNAL参数 防止send失败向系统发送消息导致关闭
    ssize_t n = send(sockfd, msg, len, flags | MSG_NOSIGNAL);
    if (n == len) {
        // 写完 通知用户
        if (cb != NULL) cb(param);
        return S_OK;
    } else if (n < 0) {
        // 出错 通知用户
        LOG(LOG_INFO_LEVEL,
            LOG_SOURCE_TCPCONNECTION,
            "sendMsg error can not deal\n");
        errorHandle_(errno, pTcpChannel_->getFd());
        return S_FALSE;
    }

    // 没写完 存起来 等待下次写
    pInfo tsi = new Info;
    tsi->offset_ = n;
    tsi->sendBuf_ = reinterpret_cast<void *>(msg);
    tsi->readBuf_ = NULL;
    (*tsi->len_) = len;
    tsi->flags_ = flags | MSG_NOSIGNAL;
    tsi->cb_ = cb;
    tsi->param_ = param;

    qSendInfo_.push(tsi);

    return S_OK;
}

// 错误处理 交给用户
int TcpConnection::onError(ErrorHandle cb)
{
    errorHandle_ = cb;
    return S_OK;
}

} // namespace net
} // namespace ndsl
