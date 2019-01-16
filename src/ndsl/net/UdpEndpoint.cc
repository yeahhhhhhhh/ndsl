////
// @file  UdpEndpoint_.cc
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
#include <iostream>
#include "ndsl/config.h"
#include "ndsl/net/UdpEndpoint.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/utils/Error.h"
#include "ndsl/net/UdpChannel.h"

namespace ndsl {
namespace net {

UdpEndpoint::UdpEndpoint(EventLoop *pLoop) 
    : sfd_(-1)
    ,pLoop_(pLoop)
    ,pUdpChannel_(NULL)
{
    cb_ = NULL;
    p_ = NULL;
}

UdpEndpoint::~UdpEndpoint() {}

// 注册sfd
int UdpEndpoint::createChannel(int sfd)
{
    pUdpChannel_ = new UdpChannel(sfd,pLoop_);
    pUdpChannel_->setCallBack(handleRead, handleWrite, this);
    pUdpChannel_->enroll(true); 
    return S_OK;
}

int UdpEndpoint::start(struct SocketAddress4 servaddr)
{
    int n = createAndBind(servaddr);
    if(n <0){
        return S_FALSE;
    }

    pUdpChannel_ = new UdpChannel(sfd_,pLoop_);
    if(pUdpChannel_ == NULL){
        return S_FALSE;
    } else {
        pUdpChannel_->setCallBack(handleRead1,NULL,this);
        pUdpChannel_->enroll(false);
    }
    return S_OK;
}

int UdpEndpoint::createAndBind(struct SocketAddress4 servaddr)
{
    sfd_ = socket(AF_INET,SOCK_DGRAM,0);
    if(sfd_ < 0){
        return S_FALSE;
    }
     // 设置非阻塞
    fcntl(sfd_, F_SETFL, O_NONBLOCK);

    if (-1 ==
        bind(sfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        printf("UdpEndpoint bind error\n");
        return S_FALSE;
    }
    return S_OK;
}

int UdpEndpoint::setInfo(
    struct sockaddr *addr,
    socklen_t addrlen,
    Callback cb,
    void *p)
{
    memset(&info, 0, sizeof(struct RecvInfo));

    info.addr_ = addr;
    info.addrlen_ = addrlen;
    info.cb_ = cb;
    info.p_ = p;

    return S_OK;
}

// 保存用户回调后的信息

int UdpEndpoint::handleRead1(void *pthis)
{
    UdpEndpoint *pThis = static_cast<UdpEndpoint *>(pthis);

    int fd;
    fd = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);


    // 设置非阻塞io
    fcntl(fd, F_SETFL, O_NONBLOCK);

        pThis->createChannel(fd);
        pThis->info.addr_ = (struct sockaddr *) &cliaddr;
        pThis->info.addrlen_ = clilen;
        if (pThis->info.cb_ != NULL) pThis->info.cb_(pThis->info.p_);

    // 测试专用
    if (pThis->cb_ != NULL) pThis->cb_(NULL);

    return S_OK;
}

// 注册起回调作用
int UdpEndpoint::onSend(
    void *buf,
    ssize_t len,
    int flags,
    struct sockaddr *dest_addr,
    socklen_t addrlen,
    Callback cb,
    void *p)
{ 
     if (NULL == pUdpChannel_) {
        return S_FALSE;
    } else {

    int sockfd = pUdpChannel_->getFd();

    int n = sendto(sockfd,buf,len,flags | MSG_NOSIGNAL,(struct sockaddr*)&dest_addr,addrlen);


    if (n == len) {
        // 写完，通知用户
        if (cb != NULL) cb(p); 
        return S_OK;
    } else if (n < 0) {      
		// error occurs, tell user
		//printf("send error");
        return S_FALSE;
    }

    // 保存发送数据的用户信息
    SendInfo_.recvBuf_ = NULL;
    SendInfo_.sendBuf_ = buf;
    SendInfo_.flags_ = flags;

    SendInfo_.len_ = new ssize_t;
    (*SendInfo_.len_) = len;

    SendInfo_.dest_addr_ = dest_addr;
    SendInfo_.addrlen_ =addrlen;
    SendInfo_.src_addr_=NULL;     // 发送仅指定目标地址 
    SendInfo_.cb_ = cb;
    SendInfo_.p_ = p;

    return S_OK;
 }
}
// udp只要有数据就发，不保证传送到目的地
int UdpEndpoint::handleWrite(void *pthis)
{
    UdpEndpoint *pThis = static_cast<UdpEndpoint *>(pthis);
    int sockfd = pThis->pUdpChannel_->getFd();
    if(sockfd < 0) { return -1;}
    
    ssize_t n;
    // 如果发送的数据报大小大于发送缓冲区，则发送失败
   if ((n = sendto(
             sockfd,
             pThis->SendInfo_.sendBuf_,
             MAXLINE,
             pThis->SendInfo_.flags_,
             pThis->SendInfo_.dest_addr_,
             pThis->SendInfo_.addrlen_))< 0) {
        // 出错
        (*pThis->SendInfo_.len_) = n;
        return S_FALSE;
    }

    (*pThis->SendInfo_.len_)=n;

    if (pThis->SendInfo_.cb_ != NULL)
        pThis->SendInfo_.cb_(pThis->SendInfo_.p_);

    return S_OK;  
}

// 如果执行成功，返回值就为 S_OK；如果出现错误，返回值就为 S_FAIL，并设置 errno 的值。
int UdpEndpoint::onRecv(
    char *buf,
    ssize_t *len,
    int flags,
    struct sockaddr *src_addr,
    socklen_t addrlen,
    Callback cb,
    void *p)
{
    int sockfd = pUdpChannel_->getFd();
    ssize_t n;

    if ((n = recvfrom(sockfd, buf, MAXLINE, flags,src_addr,&addrlen)) < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {

            // 保存用户信息
            RecvInfo_.recvBuf_ = buf;
            RecvInfo_.sendBuf_ = NULL;
            RecvInfo_.flags_ = flags | MSG_NOSIGNAL;
            RecvInfo_.len_ = len;
            RecvInfo_.src_addr_=src_addr;
            RecvInfo_.addrlen_=addrlen;
            RecvInfo_.dest_addr_ =NULL;  // 接收数据只需知道发送源
            RecvInfo_.cb_ = cb;
            RecvInfo_.p_ = p;

            return S_OK;
        } else {
			// error occurs,callback user
            return S_FALSE;
        }
    }

    (*len) = n;
	// tell user after reading successfully in one time
    if (cb != NULL) cb(p);
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

    ssize_t n;
    if ((n = recvfrom(
             sockfd,
             pThis->RecvInfo_.recvBuf_,
             MAXLINE,
             pThis->RecvInfo_.flags_,
             pThis->RecvInfo_.src_addr_,
             (&(pThis->RecvInfo_.addrlen_)))) < 0) {
        // 出错
        (*pThis->RecvInfo_.len_) = n;
        return S_FALSE;
    }

    (*pThis->RecvInfo_.len_) = n;

    // 完成数据读取之后通知mul
    if (pThis->RecvInfo_.cb_ != NULL)
        pThis->RecvInfo_.cb_(pThis->RecvInfo_.p_);

    return S_OK;
}
} // namespace net
} // namespace ndsl