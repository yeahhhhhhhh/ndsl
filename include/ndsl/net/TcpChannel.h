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

    // TODO: 还需要这个么
    // 服务器还需要用户调用onAccept么
    // TcpConnection *newConnection(int connfd, TcpAcceptor *pta);
};

} // namespace net
} // namespace ndsl

#endif // __TCPCHANNEL_H__
