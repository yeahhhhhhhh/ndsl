/**
 * @file TcpChannel.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __TCPCHANNEL_H__
#define __TCPCHANNEL_H__
#include "BaseChannel.h"
#include "TcpConnection.h"
#include "EventLoop.h"

namespace ndsl {
namespace net {

class TcpChannel : public BaseChannel
{
  public:
    TcpChannel(int sockfd, EventLoop *loop);
    ~TcpChannel();

    TcpConnection *newConnection(int connfd);
};

} // namespace net
} // namespace ndsl

#endif // __TCPCHANNEL_H__
