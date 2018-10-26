/*
 * File: TcpChannel.h
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Saturday, 20th October 2018 3:46:27 pm
 * -----
 * Copyright 2018 - 2018
 */

#ifndef __TCPCHANNEL_H__
#define __TCPCHANNEL_H__
#include "Channel.h"
#include "TcpConnection.h"

namespace ndsl {
namespace net {

class TcpChannel : public Channel
{
  private:
    TcpConnection *pCon_;

  public:
    TcpChannel(EventLoop *loop, int sockfd);

    // 回调
    int onRead(TcpConnection *pCon, char *inBuf);
    int onWrite();

    int handleEvent();
    int setCallBack(TcpConnection *pCon);
};

} // namespace net
} // namespace ndsl

#endif // __TCPCHANNEL_H__
