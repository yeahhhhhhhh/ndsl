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
// #include "EventLoop.h"
#include "TcpConnection.h"

class TcpChannel : public Channel
{
  private:
    TcpConnection *pCon_;

    // epoll事件注册
    int update();
    int regist();
    int del();

  public:
    TcpChannel(EventLoop *loop, int sockfd);

    // 回调
    int onRead(TcpConnection *pCon, char *inBuf);
    int onWrite();

    int handleEvent();
    int setCallBack(TcpConnection *pCon);
};

#endif // __TCPCHANNEL_H__
