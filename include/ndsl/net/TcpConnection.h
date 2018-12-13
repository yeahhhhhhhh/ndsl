/*
 * File: TcpConnection.h
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Wednesday, 28th November 2018 10:57:51 pm
 */

#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__
#include "TcpChannel.h"
#include "EventLoop.h"
#include "ChannelCallBack.h"
#include "../utils/temp_define.h"

namespace ndsl {
namespace net {

class TcpChannel;

class TcpConnection : public ChannelCallBack
{
  private:
    TcpChannel *pTcpChannel_;
    char inBuf_[MAXLINE];
    char outBuf_[MAXLINE];

    int createChannel(int sockfd_, EventLoop *pLoop);

  public:
    TcpConnection(int sockfd, EventLoop *pLoop);
    ~TcpConnection();

    int handleRead();
    int handleWrite();
    int send(char *outBuf);
};

} // namespace net
} // namespace ndsl

#endif // __TCPCONNECTION_H__