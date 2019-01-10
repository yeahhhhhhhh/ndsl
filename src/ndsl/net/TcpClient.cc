/**
 * @file TcpClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <arpa/inet.h>
#include <errno.h>
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/utils/Error.h"
#include "ndsl/config.h"

namespace ndsl {
namespace net {

TcpClient::TcpClient() {}

TcpClient::TcpClient(EventLoop *loop)
    : loop_(loop)
{}

int TcpClient::onConnect(ChannelCallBack cb, void *thi)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr_.setPort(SERV_PORT);

    inet_pton(AF_INET, "127.0.0.1", &servaddr_.sin_addr);

    int n;
    if ((n = connect(sockfd, (SA *) &servaddr_, sizeof(servaddr_))) < 0) {
        if (errno == EALREADY) {
            return sockfd;
        } else {
            // connect出错 返回出错
            return S_FALSE;
        }
    }

    // 创建一个Channel
    createChannel(sockfd, loop_, cb, thi);

    return S_OK;
}

int TcpClient::disConnect() {}

int TcpClient::createChannel(
    int sockfd,
    EventLoop *pLoop,
    ChannelCallBack cb,
    void *thi)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->setCallBack(cb, NULL, thi);
    pTcpChannel_->enrollIn(true);

    return S_OK;
}

} // namespace net
} // namespace ndsl
