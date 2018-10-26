/*
 * File: Channel.h
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Saturday, 20th October 2018 3:46:24 pm
 * -----
 * Copyright 2018 - 2018
 */

#ifndef __CHANNEL_H__
#define __CHANNEL_H__
#include "ndsl/net/EventLoop.h"

namespace ndsl {
namespace net {
class Channel
{
  private:
    int fd_;
    int events_;
    int revents_;
    EventLoop *pLoop_;

    // epoll事件注册
    int update();
    int regist();
    int del();

  public:
    Channel(int fd, EventLoop *loop);

    virtual int onRead() = 0;
    virtual int onWrite() = 0;
    virtual int handleEvent() = 0;

    int getFd();
    int setRevents(int revents);
    int getRevents();
    int getEvents();
    EventLoop *getEventLoop();

    int enableReading();
    int enableWriting();
    int disableWriting();
    int isWriting();
};
} // namespace net
} // namespace ndsl

} // namespace net
} // namespace ndsl

#endif // __CHANNEL_H__