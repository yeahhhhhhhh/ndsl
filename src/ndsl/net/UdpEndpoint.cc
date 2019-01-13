////
// @file  UdpEndpoint.cc
// @brief
//
//
// @author lanry
// @email luckylanry@163.com
//

#include <errno.h>
#include <unistd.h>
#include <sys/un.h>
#include "ndsl/net/UdpEndpoint.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/UdpChannel.h"

namespace ndsl {
namespace net {

UdpEndpoint::UdpEndpoint() {}
UdpEndpoint::~UdpEndpoint() {}

int UdpEndpoint::createChannel(int sockfd, EventLoop *pLoop)
{
    pUdpChannel_ = new UdpChannel(sockfd, pLoop);
    pUdpChannel_->setCallBack(handleRead, handleWrite, this);
    pUdpChannel_->enroll(true);

    return S_OK;
}

UdpChannel *UdpEndpoint::getUdpChannel()
{
    return pUdpChannel_;
}

int UdpEndpoint::send(
    const void *buf,
    size_t len,
    int flags,
    struct sockaddr *dest_addr,
    socklen_t addrlen,
    Callback cb,
    void *param)
{
    int sockfd = pUdpChannel_->getFd();
    size_t n = sendto(sockfd, buf, len, flags,dest_addr,addrlen);
    if (n == len) {
        if (cb != NULL) cb(param); // 写完发送的数据，通知
        return S_OK;
    } else if (n < 0) {      // 出错，返回-1
		// error occurs, tell user
		errorHandle_(errno, pUdpChannel_->getFd());
        return S_FAIL;
    }

    pInfo tsi = new Info;
    tsi->offset_ = n;
    tsi->sendBuf_ = buf;
    tsi->recvBuf_ = NULL;
    tsi->len_ = len;
    tsi->flags_ = flags;
    tsi->dest_addr_ = dest_addr; // 接收数据的用户数据地址
    tsi->addrlen_ = addrlen;     // 接收数据的用户地址长度
    tsi->cb_ = cb;
    tsi->param_ = param;

    qSendInfo_.push(tsi);

    pUdpChannel_->enableWriting();

    return S_OK;
}

int UdpEndpoint::handleWrite(void *pthis)
{
	UdpEndpoint *pThis = static_cast<UdpEndpoint *>(pthis);
    int sockfd = pThis->pUdpChannel_->getFd();
    if (sockfd < 0) { return -1; }
    size_t n;

    if (pThis->qSendInfo_.size() > 0) {
        pInfo tsi = pThis->qSendInfo_.front();

        if ((n = sendto(
                 sockfd,
                 (char *) tsi->sendBuf_ + tsi->offset_,
                 tsi->len_ - tsi->offset_,
                 tsi->flags_,tsi->dest_addr_,tsi->addrlen_)) > 0) {
            tsi->offset_ += n;

            if (tsi->offset_ == tsi->len_) {
                if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
                pThis->qSendInfo_.pop();    // 无写事件 注销写事件
                if (pThis->qSendInfo_.size() == 0) 
					pThis->pUdpChannel_->disableWriting();
                delete tsi; // 删除申请的内存
            } else if (n == 0) {  // 发送缓冲区满 等待下一次被调用
                return S_OK;
            }
        } else if (n < 0) {
            // 写过程中出错 出错之后处理不了 注销事件 并交给用户处理
			pThis->errorHandle_(errno, pThis->pUdpChannel_->getFd());
            pThis->qSendInfo_.pop(); 
            delete tsi;

            // 无写事件 注销写事件
            if (pThis->qSendInfo_.size() == 0) 
				pThis->pUdpChannel_->disableWriting();

            return S_FAIL;
        }
    }
    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno 的值。
int UdpEndpoint::recv(
    char *buf,
    size_t len,
    int flags,
    struct sockaddr *src_addr,
    socklen_t addrlen,
    Callback cb,
    void *param)
{
    int sockfd = pUdpChannel_->getFd();
    if ((len = recvfrom(sockfd, buf, MAXLINE, flags,src_addr,&addrlen)) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            pUdpChannel_->enableReading();

            pInfo tsi = new Info;
            tsi->recvBuf_ = buf;
            tsi->sendBuf_ = NULL;
            tsi->flags_ = flags;
            tsi->len_ = len;
            tsi->src_addr_ = src_addr; // 所接受的数据的源地址
            tsi->addrlen_ = addrlen;   // 数据源地址长度
            tsi->cb_ = cb;
            tsi->param_ = param;

            qRecvInfo_.push(tsi);
            return S_OK;
        } else {
			// error occurs,callback user
			errorHandle_(errno, pUdpChannel_->getFd());
            return S_FAIL;
        }
    }
	// tell user after reading successfully in one time
    if (cb != NULL) cb(param);
    // 先返回，最终的处理在onRead()里面
    return S_OK;
}

int UdpEndpoint::handleRead(void *pthis)
{
	UdpEndpoint *pThis = static_cast<UdpEndpoint *>(pthis);
    int sockfd = pThis->pUdpChannel_->getFd();
    if (sockfd < 0) 
	{ 
		return S_FAIL; 
	}
    pInfo tsi = pThis->qRecvInfo_.front();

    if (pThis->qRecvInfo_.size() > 0) {
        if ((tsi->len_ = recvfrom(sockfd, tsi->recvBuf_, MAXLINE, tsi->flags_,tsi->src_addr_,&tsi->addrlen_)) <0) {   // 出错就设置错误码
			// error occurs
			pThis->errorHandle_(errno, pThis->pUdpChannel_->getFd());
			return S_FAIL;
        }
    }

    // 无论出错还是完成数据读取之后都得通知用户
    if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
    pThis->qRecvInfo_.pop();
    delete tsi;

    if (pThis->qRecvInfo_.size() == 0) {  // 将读事件移除
        pThis->pUdpChannel_->disableReading();
    }

    return S_OK;
}

int UdpEndpoint::onError(ErrorHandle cb)
{
	errorHandle_ = cb;
	return S_OK;
}
} // namespace net
} // namespace ndsl