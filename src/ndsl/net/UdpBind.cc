////
// @file  UdpBind.cc
// @brief
// 
//
// @author lanry
// @email luckylanry@163.com
//

#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cstdio>
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/UdpBind.h"
#include "ndsl/net/UdpEndpoint.h"

using namespace std;

namespace ndsl {
namespace net {

UdpBind::UdpBind(EventLoop *pLoop)
    : sockfd_(-1), pLoop_(pLoop)
{
	info.inUse_ = false;
}

UdpBind::~UdpBind() { delete pUdpChannel_; }

int UdpBind::handleRead(void *pthis)
{
	UdpBind *pThis = static_cast< UdpBind *>(pthis);
    
    int sfd= pThis->sockfd_;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);

    // 设置非阻塞io
    fcntl(sfd, F_SETFL, O_NONBLOCK);

    if (pThis->info.inUse_) {
        ((pThis->info).pUdpInfo_)->createChannel(sfd, pThis->pUdpChannel_->pLoop_);
        pThis->info.addr_ = (struct sockaddr *) &cliaddr;
        pThis->info.addrlen_ = (socklen_t *) &clilen;
        if (pThis->info.cb_ != NULL) 
			pThis->info.cb_(pThis->info.param_);
        pThis->pUdpChannel_->disableReading();
    }

	// test use
	if(pThis->cb_ != NULL) pThis->cb_(NULL);
    return S_OK;
}

int UdpBind::start()
{
    create();
    pUdpChannel_ = new UdpChannel(sockfd_, pLoop_);
    pUdpChannel_->setCallBack(handleRead, NULL, this);
    pUdpChannel_->enroll(false);
	pUdpChannel_->enableReading();

    return S_OK;
}

int UdpBind::create()
{
    sockfd_ = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct SocketAddress4 servaddr;

    // 设置非阻塞
    fcntl(sockfd_, F_SETFL, O_NONBLOCK);
    servaddr.setPort(SERV_PORT);

    if (-1 ==bind(sockfd_, (struct sockaddr *) &servaddr, 
				sizeof(servaddr))) 
	{    printf("Udp bind error\n"); }

    return S_OK;
}

} // namespace net
} // namespace ndsl
