/**
 * @file TcpConnection.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpAcceptor.h"
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstdio>

namespace ndsl {
namespace net {

TcpConnection::TcpConnection(TcpAcceptor *tcpAcceptor)
    : pTcpAcceptor_(tcpAcceptor)
{}
TcpConnection::~TcpConnection() {}

int TcpConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->setCallBack(handleRead, handleWrite, this);
    pTcpChannel_->enroll(true);

    return S_OK;
}

int TcpConnection::onSend(
    void *buf,
    size_t len,
    int flags,
    Callback cb,
    void *param)
{
    int sockfd = pTcpChannel_->getFd();

    // 加上MSG_NOSIGNAL参数 防止send失败向系统发送消息导致关闭
    size_t n = send(sockfd, buf, len, flags | MSG_NOSIGNAL);
    if (n == len) {
        // 写完 通知用户
        if (cb != NULL) cb(param);
        // 释放掉buf占用的空间
        if (buf != NULL) free(buf);
        return S_OK;
    } else if (n < 0) {
        // 出错 通知用户
        errorHandle_(errno, pTcpChannel_->getFd());
        // 释放掉buf占用的空间
        if (buf != NULL) free(buf);
        return S_FAIL;
    }

    pInfo tsi = new Info;
    tsi->offset_ = n;
    tsi->sendBuf_ = buf;
    tsi->readBuf_ = NULL;
    (*tsi->len_) = len;
    tsi->flags_ = flags | MSG_NOSIGNAL;
    tsi->cb_ = cb;
    tsi->param_ = param;

    qSendInfo_.push(tsi);

    return S_OK;
}

int TcpConnection::handleWrite(void *pthis)
{
    TcpConnection *pThis = static_cast<TcpConnection *>(pthis);
    int sockfd = pThis->pTcpChannel_->getFd();

    if (sockfd < 0) { return -1; }
    size_t n;

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
                // 释放掉buf占用的空间
                if (tsi->sendBuf_ != NULL) free(tsi->sendBuf_);

                delete tsi; // 删除申请的内存
            } else if (n == 0) {
                // 发送缓冲区满 等待下一次被调用
                return S_OK;
            }
        } else if (n < 0) {
            // 写过程中出错 出错之后处理不了 注销事件 并交给用户处理
            pThis->errorHandle_(errno, pThis->pTcpChannel_->getFd());

            // 将事件从队列中移除
            pThis->qSendInfo_.pop();

            // 释放掉buf占用的空间
            if (tsi->sendBuf_ != NULL) free(tsi->sendBuf_);
            delete tsi;

            return S_FAIL;
        }
    }
    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno
// 的值。
int TcpConnection::onRecv(
    char *buf,
    size_t *len,
    int flags,
    Callback cb,
    void *param)
{
    int sockfd = pTcpChannel_->getFd();
    if (((*len) = recv(sockfd, buf, MAXLINE, flags)) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            // 保存用户信息
            RecvInfo_.readBuf_ = buf;
            RecvInfo_.sendBuf_ = NULL;
            RecvInfo_.flags_ = flags;
            RecvInfo_.len_ = len;
            RecvInfo_.cb_ = cb;
            RecvInfo_.param_ = param;

            return S_OK;
        } else {
            // 出错 回调用户
            errorHandle_(errno, pTcpChannel_->getFd());
            return S_FAIL;
        }
    }
    // 一次性读完之后通知用户
    if (cb != NULL) cb(param);
    return S_OK;
}

int TcpConnection::handleRead(void *pthis)
{
    TcpConnection *pThis = static_cast<TcpConnection *>(pthis);
    int sockfd = pThis->pTcpChannel_->getFd();
    if (sockfd < 0) { return S_FAIL; }

    if (((*pThis->RecvInfo_.len_) = recv(
             sockfd,
             pThis->RecvInfo_.readBuf_,
             MAXLINE,
             pThis->RecvInfo_.flags_)) < 0) {
        // 出错
        pThis->errorHandle_(errno, pThis->pTcpChannel_->getFd());
        return S_FAIL;
    }

    // 完成数据读取之后通知mul
    if (pThis->RecvInfo_.cb_ != NULL)
        pThis->RecvInfo_.cb_(pThis->RecvInfo_.param_);

    return S_OK;
} // namespace net

int TcpConnection::onAccept(
    TcpConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    pTcpAcceptor_->setInfo(pCon, addr, addrlen, cb, param);

    return S_OK;
}

int TcpConnection::sendMsg(
    struct msghdr *msg,
    int flags,
    Callback cb,
    void *param)
{
    int sockfd = pTcpChannel_->getFd();
    size_t len = sizeof(struct msghdr);

    // 加上MSG_NOSIGNAL参数 防止send失败向系统发送消息导致关闭
    size_t n = send(sockfd, msg, len, flags | MSG_NOSIGNAL);
    if (n == len) {
        // 写完 通知用户
        if (cb != NULL) cb(param);
        return S_OK;
    } else if (n < 0) {
        // 出错 通知用户
        errorHandle_(errno, pTcpChannel_->getFd());
        return S_FAIL;
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
