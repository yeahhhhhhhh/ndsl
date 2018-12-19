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
{
    // 将自身注册到eventloop上面
    this->regist();
}

TcpChannel::~TcpChannel()
{
    // 将自身从eventloop上面删掉
    del();
}

int TcpChannel::getFd() { return sockfd_; }

TcpConnection *TcpChannel::newConnection(int connfd)
{
    TcpConnection *pCon = new TcpConnection(connfd, pLoop_);
    return pCon;
}

} // namespace net
} // namespace ndsl
