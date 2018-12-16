/**
 * @file TcpAcceptor.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __TCPACCEPTOR_H__
#define __TCPACCEPTOR_H__

#include "Channel.h"
#include "TcpChannel.h"
#include "EventLoop.h"

namespace ndsl {
namespace net {

class TcpAcceptor : public ChannelCallBack
{
  private:
    int listenfd_;
    EventLoop *pLoop;
    TcpChannel *pTcpChannel_;

  public:
    TcpAcceptor(int listenfd, EventLoop *pLoop);
    int handleRead();
    int handleWrite();
    int start();

  private:
    int createAndListen();
};

} // namespace net
} // namespace ndsl

#endif // __TCPACCEPTOR_H__