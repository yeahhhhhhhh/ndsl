/*
 * File: TcpConnection.h
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Saturday, 20th October 2018 3:46:35 pm
 * -----
 * Copyright 2018 - 2018
 */

#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__
#include "TcpChannel.h"
#include "EventLoop.h"

class TcpConnection
{
  private:
    TcpChannel *pTcpChannel_;
    char inBuf_[MAXLINE];
    char outBuf_[MAXLINE];

    int createChannel(int sockfd_, EventLoop *pLoop);

  public:
    TcpConnection(int sockfd, EventLoop *pLoop);
    ~TcpConnection();

    int read();
    int write();
    int send(char *outBuf);
};

#endif // __TCPCONNECTION_H__