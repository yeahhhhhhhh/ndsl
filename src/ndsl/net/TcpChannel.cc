/**
 * @file TcpChannel.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpConnection.h"

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

TcpConnection *TcpChannel::newConnection(int connfd, TcpAcceptor *pTa)
{
    TcpConnection *pCon = new TcpConnection(pTa);
    pCon->createChannel(connfd, pLoop);
    return pCon;
}

} // namespace net
} // namespace ndsl
