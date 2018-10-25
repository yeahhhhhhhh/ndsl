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
#include "EventLoop.h"

class TcpChannel : public Channel
{
  private:
    int sockfd_;
    int events_;
    EventLoop *pLoop;

    int update();
    int register();

  public:
    int onRead(TcpConnection *pCon, char *inBuf);
    int onWrite();

    int enableReading();
    int enableWriting();
    int disableWriting();
    int getEvents();
    int getFd();
};

#endif // __TCPCHANNEL_H__
