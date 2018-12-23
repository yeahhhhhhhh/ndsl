/**
 * @file BaseChannel.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __BASECHANNEL_H__
#define __BASECHANNEL_H__

#include "Channel.h"

namespace ndsl {
namespace net {

class EventLoop;

class BaseChannel : public Channel
{
  private:
    int fd_;
    int update();

    ChannelCallBack *pCb_;
    // using Callback = void (*)(void *); // Callback 函数指针原型
    // using ChannelCallBack = int (*)();

  public:
    BaseChannel(int fd, EventLoop *loop);

    // 指向被调用的函数
    // ChannelCallBack handleRead_, handleWrite_;

    int handleEvent();
    int getFd();

    // epoll 事件管理
    int del();
    int regist(bool isET);
    int enableReading();
    int enableWriting();
    int disableReading();
    int disableWriting();

    // int setCallBack(ChannelCallBack handleRead, ChannelCallBack handleWrite);
    int setCallBack(void *cb);
};

} // namespace net
} // namespace ndsl

#endif // __BASECHANNEL_H__