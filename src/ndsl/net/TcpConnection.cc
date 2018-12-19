/**
 * @file TcpConnection.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */

#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/temp_define.h"
#include <unistd.h>

namespace ndsl {
namespace net {

TcpConnection::TcpConnection(int sockfd, EventLoop *pLoop)
{
    createChannel(sockfd, pLoop);
}
TcpConnection::~TcpConnection() {}

int TcpConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->setCallBack(this);

    return S_OK;
}

int TcpConnection::onSend(
    const void *buf,
    size_t len,
    int flags,
    Callback cb,
    void *param,
    int &errn)
{
    int sockfd = pTcpChannel_->getFd();
    int n = write(sockfd, buf, len);
    if (n == len) {
        // 写完 通知用户
        if (cb != NULL) cb(param);
        return S_OK;
    } else if (n < 0) {
        // 出错 通知用户
        errn = errno;
        return S_FAIL;
    }

    pInfo tsi = new Info;
    tsi->offset_ = n;
    tsi->buf_ = buf;
    tsi->len_ = len;
    tsi->flags_ = flags;
    tsi->cb_ = cb;
    tsi->param_ = param;
    tsi->errno_ = errno;

    qSendInfo_.push(tsi);

    pTcpChannel_->enableWriting();

    return S_OK;
}

int TcpConnection::handleWrite()
{
    int sockfd = pTcpChannel_->getFd();

    cout << "fd = " << sockfd << endl;

    if (sockfd < 0) { return -1; }
    int n;

    if (qSendInfo_.size() > 0) {
        pInfo tsi = qSendInfo_.front();

        if ((n = write(
                 sockfd, tsi->buf_ + tsi->offset_, tsi->len_ - tsi->offset_)) >
            0) {
            tsi->offset_ += n;

            if (tsi->offset_ == tsi->len_) {
                if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
                qSendInfo_.pop();
                // 无写事件 注销写事件
                if (qSendInfo_.size() == 0) pTcpChannel_->disableWriting();
                delete tsi; // 删除申请的内存
            } else if (n == 0) {
                // 发送缓冲区满 等待下一次被调用
                return S_OK;
            }
        } else if (n < 0) {
            // 写过程中出错 出错之后处理不了 注销事件 并交给用户处理
            tsi->errno_ = ::errno;
            if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);

            qSendInfo_.pop();
            delete tsi;

            // 无写事件 注销写事件
            if (qSendInfo_.size() == 0) pTcpChannel_->disableWriting();

            return S_FAIL;
        }
    }
    return S_OK;
}

int TcpConnection::handleRead()
{
    int sockfd = pTcpChannel_->getFd();
    if (sockfd < 0) { return S_FAIL; }

    if (qRecvInfo_.size() > 0) {
        pinfo tsi = qRecvInfo_.push();
        if ((tsi->len_ = read(sockfd, tsi->buf_, MAXLINE)) < 0) {
            // 出错就设置错误码
            tsi->errno_ = ::errno;
        }
    }

    // 无论出错还是完成数据读取之后都得通知用户
    if (recvInfo_.cb != NULL) recvInfo_.cb_(recvInfo_.param_);
    qRecvInfo_.pop();
    delete tsi;
    if (qRecvInfo_.size() == 0) {
        // 将读事件移除
        pTcpChannel_->disableReading();
    }

    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno
// 的值。
int TcpConnection::onRecv(
    char *buf,
    int &len,
    Callback cb,
    void *param,
    int &errn)
{
    int sockfd = pTcpChannel_->getFd();
    if ((len = read(sockfd, buf, MAXLINE)) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            pTcpChannel_->enableReading();

            pInfo tsi = new Info;
            tsi.buf_ = buf;
            tsi.len_ = len;
            tsi.cb_ = cb;
            tsi.param_ = param;
            tsi.errno_ = errno;

            qRecvInfo_.push(tsi);
            return S_OK;
        } else {
            errn = errno;
            return S_FAIL;
        }
    }
    if (cb != NULL) cb(param);
    // 先返回，最终的处理在onRead()里面
    return S_OK;
}

int TcpConnection::onRecvmsg(char *buf, Callback cb, void *param, int &errn)
{
    // 异步
}

// int onAccept(
// TcpConnection *pCon,
// struct sockaddr *addr,
// socklen_t *addrlen,
// Callback cb,
// void *param);
int TcpConnection::onAccept(
    TcpConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    // onAcceptor()和TcpAcceptor函数的功能不重复么

    int connfd;
    if ((connfd = accept(pTcpChannel_->getFd(), addr, addrlen)) > 0) {
        // accept成功
        TcpChannel *pTcpChannel = new TcpChannel(connfd, getEventLoop());
        pTcpChannel->setCallBack(this);

        pCon->pTcpChannel_ = pTcpChannel;

        if (cb != NULL) cb(param);
    } else {
        // accept不成功，转异步处理
        // 异步理解为用户没有启TcpAcceptor函数
        TcpAcceptor *ta = new TcpAcceptor(
            pTcpChannel_->getFd(),
            getEventLoop(),
            pCon,
            addr,
            addrlen,
            cb,
            param);
        ta->start();
    }

    return S_OK;
}

} // namespace net
} // namespace ndsl
