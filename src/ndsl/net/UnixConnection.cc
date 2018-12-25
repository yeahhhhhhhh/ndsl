////
// @brief 
// unixconnection shixian
//
// @author ranxiangjun
// @email ranxianshen@gmail.com
//
#include <errno.h>
#include <unistd.h>
#include <sys/un.h>
#include "../../../include/ndsl/net/UnixConnection.h"
#include "../../../include/ndsl/utils/temp_define.h"
#include "../../../include/ndsl/net/UnixChannel.h"
#include "../../../include/ndsl/net/UnixAcceptor.h"

namespace ndsl {
namespace net {

UnixConnection::UnixConnection() {}
UnixConnection::~UnixConnection() {}

int UnixConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pUnixChannel_ = new UnixChannel(sockfd, pLoop);
    pUnixChannel_->setCallBack(handleRead, handleWrite, this);
    pUnixChannel_->regist(true);

    return S_OK;
}

int UnixConnection::onSend(
    const void *buf,
    size_t len,
    int flags,
    Callback cb,
    void *param,
    int &errn)
{
    int sockfd = pUnixChannel_->getFd();
    size_t n = send(sockfd, buf, len, flags);
    if (n == len) {
        // 写完 通知用户
        if (cb != NULL) cb(param);
        return S_OK;
    } else if (n < 0) {      // 出错 通知用户
        errn = errno;
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
    *tsi->errno_ = errno;

    qSendInfo_.push(tsi);

    pUnixChannel_->enableWriting();

    return S_OK;
}

int UnixConnection::handleWrite(void *pthis)
{
	UnixConnection *pThis = static_cast<UnixConnection *>(pthis);
    int sockfd = pThis->pUnixChannel_->getFd();
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
                pThis->qSendInfo_.pop();    // 无写事件 注销写事件
                if (pThis->qSendInfo_.size() == 0) pThis->pUnixChannel_->disableWriting();
                delete tsi; // 删除申请的内存
            } else if (n == 0) {  // 发送缓冲区满 等待下一次被调用
                return S_OK;
            }
        } else if (n < 0) {
            // 写过程中出错 出错之后处理不了 注销事件 并交给用户处理
            *tsi->errno_ = errno;
            if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);

            pThis->qSendInfo_.pop();
            delete tsi;

            // 无写事件 注销写事件
            if (pThis->qSendInfo_.size() == 0) pThis->pUnixChannel_->disableWriting();

            return S_FAIL;
        }
    }
    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno 的值。
int UnixConnection::onRecv(
    char *buf,
    size_t &len,
    int flags,
    Callback cb,
    void *param,
    int &errn)
{
    int sockfd = pUnixChannel_->getFd();
    if ((len = recv(sockfd, buf, MAXLINE, flags)) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            pUnixChannel_->enableReading();

            pInfo tsi = new Info;
            tsi->readBuf_ = buf;
            tsi->sendBuf_ = NULL;
            tsi->flags_ = flags;
            tsi->len_ = len;
            tsi->cb_ = cb;
            tsi->param_ = param;
            *tsi->errno_ = errno;

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

int UnixConnection::handleRead(void *pthis)
{
	UnixConnection *pThis = static_cast<UnixConnection *>(pthis);
    int sockfd = pThis->pUnixChannel_->getFd();
    if (sockfd < 0) { return S_FAIL; }
    pInfo tsi = pThis->qRecvInfo_.front();

    if (pThis->qRecvInfo_.size() > 0) {
        if ((tsi->len_ = recv(sockfd, tsi->readBuf_, MAXLINE, tsi->flags_)) <0) {   // 出错就设置错误码
            *tsi->errno_ = errno;
        }
    }

    // 无论出错还是完成数据读取之后都得通知用户
    if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
    pThis->qRecvInfo_.pop();
    delete tsi;
    if (pThis->qRecvInfo_.size() == 0) {  // 将读事件移除
        pThis->pUnixChannel_->disableReading();
    }

    return S_OK;
}

int UnixConnection::onRecvmsg(char *buf, Callback cb, void *param, int &errn)
{
    // 异步
    return S_OK;
}

int UnixConnection::onAccept(
    UnixConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    int connfd;
    if ((connfd = accept(pUnixChannel_->getFd(), addr, addrlen)) > 0) {
        // accept成功
        UnixConnection *pUnixCon = new UnixConnection();
        pUnixCon->createChannel(connfd, pUnixChannel_->getEventLoop());
        // pUnixChannel->setCallBack(this);

        // pCon->pUnixChannel_ = pUnixChannel;

        if (cb != NULL) cb(param);
    } else {
        // accept不成功，转异步处理
        // 异步理解为用户没有启UnixAcceptor函数
        UnixAcceptor *ta = new UnixAcceptor(
            pUnixChannel_->getEventLoop(),
            pCon,
            addr,
            addrlen,
            cb,
            param);
        ta->start(((sockaddr_un*)addr)->sun_path);
    }

    return S_OK;
}

} // namespace net
} // namespace ndsl
