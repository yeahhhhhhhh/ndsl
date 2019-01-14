////
// @file  UdpEndpoint.cc
// @brief
//
//
// @author lanry
// @email luckylanry@163.com
//

#include <sys/socket.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <errno.h>
#include <unistd.h>
#include <sys/un.h>
#include "ndsl/net/UdpEndpoint.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/utils/Error.h"
#include "ndsl/net/UdpChannel.h"

namespace ndsl {
namespace net {

UdpEndpoint::UdpEndpoint(EventLoop *pLoop) 
{
    pLoop_ = pLoop;
}

UdpEndpoint::~UdpEndpoint() {}


int UdpEndpoint::createChannel(int sockfd_,Callback cb,void *param)
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);

    struct SocketAddress4 servaddr;

    // 设置非阻塞
    fcntl(sockfd_, F_SETFL, O_NONBLOCK);
    // setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    servaddr.setPort(SERV_PORT);

    if (-1 ==
        bind(sockfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        printf("UdpEndpoint bind error\n");
    }

    cb_= cb;
    param_ = param;

    pUdpChannel_ = new UdpChannel(sockfd_, pLoop_);
    pUdpChannel_->setCallBack(handleRead, handleWrite, this);
    pUdpChannel_->enroll(true); 
    
    return S_OK;
}

int UdpEndpoint::handleRead1(void *pthis)
{
    UdpEndpoint *pThis = static_cast<UdpEndpoint *>(pthis);

    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);

    struct SocketAddress4 cliaddr;
    socklen_t clilen = sizeof(struct SocketAddress4);


    // 设置非阻塞io
    fcntl(fd, F_SETFL, O_NONBLOCK);

        pThis->createChannel(fd, pThis->cb_,pThis->param_);
        pThis->info.addr_ = (struct sockaddr *) &cliaddr;
        pThis->info.addrlen_ = (socklen_t *) &clilen;
        if (pThis->info.cb_ != NULL) pThis->info.cb_(pThis->info.param_);

    // 测试专用
    if (pThis->cb_ != NULL) pThis->cb_(NULL);

    return S_OK;
}

int UdpEndpoint::setInfo(
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    memset(&info, 0, sizeof(struct RecvInfo));

    info.addr_ = addr;
    info.addrlen_ = addrlen;
    info.cb_ = cb;
    info.param_ = param;

    return S_OK;
}

int UdpEndpoint::onSend(
    const void *buf,
    size_t len,
    int flags,
    struct sockaddr *dest_addr,
    socklen_t addrlen,
    Callback cb,
    void *param)
{ 
    int sockfd = pUdpChannel_->getFd();
    size_t n = sendto(sockfd, buf, len, flags,(struct sockaddr*)&dest_addr,addrlen);
    if (n == len) {
        // 写完，通知用户
        if (cb != NULL) cb(param); 
        return S_OK;
    } else if (n < 0) {      
		// error occurs, tell user
		printf("send error");
        return S_FALSE;
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
                delete tsi; // 删除申请的内存
            } else if (n == 0) {  // 发送缓冲区满 等待下一次被调用
                return S_OK;
            }
        } else if (n < 0) {
            printf("send error other\n");
    
            // 将事件从队列中移除
            pThis->qSendInfo_.pop(); 
            delete tsi;

            return S_FALSE;
        }
    }
    return S_OK;
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno 的值。
int UdpEndpoint::onRecv(
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
            return S_FALSE;
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
		return S_FALSE; 
	}
    pInfo tsi = pThis->qRecvInfo_.front();

    if (pThis->qRecvInfo_.size() > 0) {
        if ((tsi->len_ = recvfrom(sockfd, tsi->recvBuf_, MAXLINE, tsi->flags_,tsi->src_addr_,&tsi->addrlen_)) <0) {   // 出错就设置错误码
			// error occurs
			return S_FALSE;
        }
    }

    // 无论出错还是完成数据读取之后都得通知用户
    if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
    pThis->qRecvInfo_.pop();
    delete tsi;

    return S_OK;
}

int UdpEndpoint::remove()
{
    pUdpChannel_->erase();
    return S_OK;
}
} // namespace net
} // namespace ndsl