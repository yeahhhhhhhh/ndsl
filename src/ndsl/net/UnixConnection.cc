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

UnixConnection::UnixConnection(UnixAcceptor *unixAcceptor)
	:pUnixAcceptor_(unixAcceptor){}
UnixConnection::~UnixConnection() {}

int UnixConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pUnixChannel_ = new UnixChannel(sockfd, pLoop);
    pUnixChannel_->setCallBack(handleRead, handleWrite, this);
    pUnixChannel_->enroll(true);

    return S_OK;
}

int UnixConnection::onSend(
    const void *buf,
    size_t len,
    int flags,
    Callback cb,
    void *param)
{
    int sockfd = pUnixChannel_->getFd();
    size_t n = send(sockfd, buf, len, flags);
    if (n == len) {
        // 写完 通知用户
        if (cb != NULL) cb(param);
        return S_OK;
    } else if (n < 0) {      // 出错 通知用户
		// error occurs, tell user
		errorHandle_(errno, pUnixChannel_->getFd());
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
                if (pThis->qSendInfo_.size() == 0) 
					pThis->pUnixChannel_->disableWriting();
                delete tsi; // 删除申请的内存
            } else if (n == 0) {  // 发送缓冲区满 等待下一次被调用
                return S_OK;
            }
        } else if (n < 0) {
            // 写过程中出错 出错之后处理不了 注销事件 并交给用户处理
			pThis->errorHandle_(errno, pThis->pUnixChannel_->getFd());
            pThis->qSendInfo_.pop();
            delete tsi;

            // 无写事件 注销写事件
            if (pThis->qSendInfo_.size() == 0) 
				pThis->pUnixChannel_->disableWriting();

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
    void *param)
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

            qRecvInfo_.push(tsi);
            return S_OK;
        } else {
			// error occurs,callback user
			errorHandle_(errno, pUnixChannel_->getFd());
            return S_FAIL;
        }
    }
	// tell user after reading successfully in one time
    if (cb != NULL) cb(param);
    // 先返回，最终的处理在onRead()里面
    return S_OK;
}

int UnixConnection::handleRead(void *pthis)
{
	UnixConnection *pThis = static_cast<UnixConnection *>(pthis);
    int sockfd = pThis->pUnixChannel_->getFd();
    if (sockfd < 0) 
	{ 
		return S_FAIL; 
	}
    pInfo tsi = pThis->qRecvInfo_.front();

    if (pThis->qRecvInfo_.size() > 0) {
        if ((tsi->len_ = recv(sockfd, tsi->readBuf_, MAXLINE, tsi->flags_)) <0) {   // 出错就设置错误码
			// error occurs
			pThis->errorHandle_(errno, pThis->pUnixChannel_->getFd());
			return S_FAIL;
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

int UnixConnection::onAccept(
    UnixConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
	pUnixAcceptor_->setInfo(pCon, addr, addrlen, cb, param);
	pUnixAcceptor_->getUnixChannel()->enableReading();

	return S_OK;
}

int UnixConnection::onError(ErrorHandle cb)
{
	errorHandle_ = cb;
	return S_OK;
}

} // namespace net
} // namespace ndsl
