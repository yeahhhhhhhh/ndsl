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
    : sockfd_(sockfd)
    , pLoop_(loop)
{}

int TcpChannel::getFd() { return sockfd_; }

int TcpChannel::newConnection(int connfd)
{
    TcpConnection *pCon = new TcpConnection(connfd, pLoop_);
}

} // namespace net
} // namespace ndsl
