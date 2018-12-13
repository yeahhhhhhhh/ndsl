/*
 * File: TcpChannel.h
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Thursday, 29th November 2018 10:42:13 am
 */

#ifndef __TCPCHANNEL_H__
#define __TCPCHANNEL_H__
#include "Channel.h"
#include "TcpConnection.h"
#include "ChannelCallBack.h"
#include "EventLoop.h"

namespace ndsl {
namespace net {

class TcpConnection;

class TcpChannel : public Channel
{
  private:
    int sockfd_;
    uint32_t events_;
    uint32_t revents_;
    EventLoop *pLoop_;
    ChannelCallBack *pCallBack_;

    // epoll事件注册
    int update();
    int regist();
    int del();

  public:
    TcpChannel(int sockfd, EventLoop *loop);
    // ~Channel();

    // 回调
    int onRead(char *inBuf);
    int onWrite();

    int getFd();
    uint32_t getRevents();
    int setRevents(uint32_t revents);
    uint32_t getEvents();
    EventLoop *getEventLoop();

    int handleEvent();
    int setCallBack(ChannelCallBack *pCB);

    // epoll 事件管理
    int enableReading();
    int enableWriting();
    int disableWriting();
    int isWriting();
};

} // namespace net
} // namespace ndsl

#endif // __TCPCHANNEL_H__
