/**
 * @file TcpChannel.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/TcpChannel.h"

namespace ndsl {
namespace net {

TcpChannel::TcpChannel(int sockfd, EventLoop *loop)
    : BaseChannel(sockfd, loop)
{}

TcpChannel::~TcpChannel()
{
    // 将自身从eventloop上面删掉
    del();
}

TcpConnection *TcpChannel::newConnection(int connfd)
{
    TcpConnection *pCon = new TcpConnection();
    pCon->createChannel(connfd, getEventLoop());
    return pCon;
}

} // namespace net
} // namespace ndsl
