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
    size_t n = send(sockfd, buf, len, flags);
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
    tsi->len_ = len;
    tsi->flags_ = flags;
    tsi->cb_ = cb;
    tsi->param_ = param;

    qSendInfo_.push(tsi);
    pTcpChannel_->enableWriting();

    return S_OK;
}

int TcpConnection::handleWrite(void *pthis)
{
    TcpConnection *pThis = static_cast<TcpConnection *>(pthis);
    int sockfd = pThis->pTcpChannel_->getFd();

    if (sockfd < 0) { return -1; }
    size_t n;

    if (pThis->qSendInfo_.size() > 0) {
        pInfo tsi = pThis->qSendInfo_.front();

        if ((n = send(
                 sockfd,
                 (char *) tsi->sendBuf_ + tsi->offset_,
                 tsi->len_ - tsi->offset_,
                 tsi->flags_)) > 0) {
            tsi->offset_ += n;

            if (tsi->offset_ == tsi->len_) {
                if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
                pThis->qSendInfo_.pop();
                // 无写事件 注销写事件
                if (pThis->qSendInfo_.size() == 0)
                    pThis->pTcpChannel_->disableWriting();
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

            pThis->qSendInfo_.pop();

            // 释放掉buf占用的空间
            if (tsi->sendBuf_ != NULL) free(tsi->sendBuf_);

            delete tsi;

            // 无写事件 注销写事件
            if (pThis->qSendInfo_.size() == 0)
                pThis->pTcpChannel_->disableWriting();

            return S_FAIL;
        }
    }
    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno
// 的值。
int TcpConnection::onRecv(
    char *buf,
    size_t &len,
    int flags,
    Callback cb,
    void *param)
{
    int sockfd = pTcpChannel_->getFd();
    if ((len = recv(sockfd, buf, MAXLINE, flags)) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            pTcpChannel_->enableReading();

            pInfo tsi = new Info;
            tsi->readBuf_ = buf;
            tsi->sendBuf_ = NULL;
            tsi->flags_ = flags;
            tsi->len_ = len;
            tsi->cb_ = cb;
            tsi->param_ = param;

            qRecvInfo_.push(tsi);
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
    pInfo tsi = pThis->qRecvInfo_.front();

    if (pThis->qRecvInfo_.size() > 0) {
        if ((tsi->len_ = recv(sockfd, tsi->readBuf_, MAXLINE, tsi->flags_)) <
            0) {
            // 出错
            pThis->errorHandle_(errno, pThis->pTcpChannel_->getFd());
            return S_FAIL;
        }
    }

    // 完成数据读取之后得通知用户
    if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
    pThis->qRecvInfo_.pop();
    delete tsi;
    if (pThis->qRecvInfo_.size() == 0) {
        // 将读事件移除
        pThis->pTcpChannel_->disableReading();
    }

    return S_OK;
}

int TcpConnection::onAccept(
    TcpConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    pTcpAcceptor_->setInfo(pCon, addr, addrlen, cb, param);
    pTcpAcceptor_->getTcpChannel()->enableReading();

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
