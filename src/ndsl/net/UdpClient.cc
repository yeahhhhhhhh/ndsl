////
// @file  UdpClient.cc
// @brief
//
//
// @author lanry
// @email luckylanry@163.com
//
#include <arpa/inet.h>
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/UdpClient.h"
#include "ndsl/net/UdpChannel.h"
#include "ndsl/config.h"
#include "ndsl/utils/Error.h"

namespace ndsl {
namespace net {

UdpClient::UdpClient() {}
UdpClient::~UdpClient() {}

UdpEndpoint *UdpClient::begin(EventLoop *loop)
{
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    struct SocketAddress4 servaddr;
    servaddr.setPort(SERV_PORT);

    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    int n;
    UdpEndpoint *ue = new UdpEndpoint();

    ue->pUdpChannel_ = new UdpChannel(sfd, loop);
    ue->pUdpChannel_->setCallBack(UdpEndpoint::handleRead, NULL, ue);
    n = ue->pUdpChannel_->enrollIn(true);

    return ue;
}

int UdpClient::end()
{
    close(sfd);
    return S_OK;
}
} // namespace net
} // namespace ndsl
