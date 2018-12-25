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

namespace ndsl {
namespace net {

class TcpAcceptor;
class TcpConnection;

class TcpChannel : public BaseChannel
{
  public:
    TcpChannel(int sockfd, EventLoop *loop);
    ~TcpChannel();

    TcpConnection *newConnection(int connfd, TcpAcceptor *pta);
};

} // namespace net
} // namespace ndsl

#endif // __TCPCHANNEL_H__
