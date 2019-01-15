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

#include "ndsl/config.h"
#include "ndsl/net/UdpEndpoint.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/utils/Error.h"
#include "ndsl/net/UdpChannel.h"

namespace ndsl {
namespace net {


UdpEndpoint::UdpEndpoint()
    : pUdpChannel_(NULL)
{}
UdpEndpoint::UdpEndpoint(EventLoop *pLoop) 
    : sockfd_(-1)
    ,pLoop_(pLoop)
    ,pUdpChannel_(NULL)
{
    cb_ = NULL;
}

UdpEndpoint::~UdpEndpoint() {}


int UdpEndpoint::createChannel(int sockfd,EventLoop *pLoop)
{
    pUdpChannel_ = new UdpChannel(sockfd, pLoop);
    pUdpChannel_->setCallBack(handleRead, handleWrite, this);
    return pUdpChannel_->enroll(true); 
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

int UdpEndpoint::start(struct SocketAddress4 servaddr)
{
    int n = createAndBind(servaddr);
    if(n <0){
        return S_FALSE;
    }

    pUdpChannel_ = new UdpChannel(sockfd_,pLoop_);
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
    sockfd_ = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd_ < 0){
        return S_FALSE;
    }

    // struct SocketAddress4 servaddr;
     // 设置非阻塞
    fcntl(sockfd_, F_SETFL, O_NONBLOCK);
   
    servaddr.setPort(SERV_PORT);

    if (-1 ==
        bind(sockfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        printf("UdpEndpoint bind error\n");
        return S_FALSE;
    }
    return S_OK;
}

int UdpEndpoint::handleRead1(void *pthis)
{
    UdpEndpoint *pThis = static_cast<UdpEndpoint *>(pthis);

    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);


    // 设置非阻塞io
    fcntl(fd, F_SETFL, O_NONBLOCK);

        pThis->createChannel(fd, pThis->pUdpChannel_->pLoop_);
        pThis->info.addr_ = (struct sockaddr *) &cliaddr;
        pThis->info.addrlen_ = (socklen_t *) &clilen;
        if (pThis->info.cb_ != NULL) pThis->info.cb_(pThis->info.param_);

    // 测试专用
    if (pThis->cb_ != NULL) pThis->cb_(NULL);

    return S_OK;
}

int UdpEndpoint::onSend(
    void *buf,
    ssize_t len,
    int flags,
    struct sockaddr *dest_addr,
    socklen_t addrlen,
    Callback cb,
    void *param)
{ 
    int sockfd = pUdpChannel_->getFd();

    ssize_t n = sendto(sockfd, buf, len, flags,(struct sockaddr*)&dest_addr,addrlen);
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
    tsi->sendBuf_ =(void *)buf;
    tsi->recvBuf_ = NULL;

    tsi->len_= new ssize_t;
    (*tsi->len_) = len;

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
    ssize_t n;

    if (pThis->qSendInfo_.size() > 0) {
        pInfo tsi = pThis->qSendInfo_.front();

        if ((n = sendto(
                 sockfd,
                 (char *) tsi->sendBuf_ + tsi->offset_,
                 (*tsi->len_ )- tsi->offset_,
                 tsi->flags_,tsi->dest_addr_,tsi->addrlen_)) > 0) {
            tsi->offset_ += n;

            if (tsi->offset_ == (*tsi->len_)) {
                if (tsi->cb_ != NULL) tsi->cb_(tsi->param_);
                pThis->qSendInfo_.pop();    // 无写事件 注销写事件


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
    ssize_t *len,
    int flags,
    struct sockaddr *src_addr,
    socklen_t addrlen,
    Callback cb,
    void *param)
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
            RecvInfo_.cb_ = cb;
            RecvInfo_.param_ = param;

            return S_OK;
        } else {
			// error occurs,callback user
            return S_FALSE;
        }
    }

    (*len) = n;
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

    ssize_t n;
    if ((n = recv(
             sockfd,
             pThis->RecvInfo_.recvBuf_,
             MAXLINE,
             pThis->RecvInfo_.flags_)) < 0) {
        // 出错
        (*pThis->RecvInfo_.len_) = n;
        return S_FALSE;
    }

    (*pThis->RecvInfo_.len_) = n;

    // 完成数据读取之后通知mul
    if (pThis->RecvInfo_.cb_ != NULL)
        pThis->RecvInfo_.cb_(pThis->RecvInfo_.param_);

    return S_OK;
}

 int UdpEndpoint::onData(
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param)
 {

     return setInfo(addr,addrlen,cb,param);
  }

// int UdpEndpoint::remove()
// {
//     pUdpChannel_->erase();
//     return S_OK;
// }
} // namespace net
} // namespace ndsl