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
#include "EventLoop.h"

namespace ndsl {
namespace net {

class TcpChannel : public BaseChannel
{
  private:
    int sockfd_;

  public:
    TcpChannel(int sockfd, EventLoop *loop);
    ~TcpChannel();

    int getFd();

    int newConnection(int connfd);
};

} // namespace net
} // namespace ndsl

#endif // __TCPCHANNEL_H__
