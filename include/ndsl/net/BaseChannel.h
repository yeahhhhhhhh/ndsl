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

class BaseChannel
    : public Channel
    , public ChannelCallBack
{
  private:
    int fd_;
    int update(bool isET);

    // ChannelCallBack *pCb_;
    // using Callback = void (*)(void *); // Callback 函数指针原型
    using ChannelCallBack = int (*)();

  public:
    BaseChannel(int fd, EventLoop *loop);

    // 指向被调用的函数
    ChannelCallBack handleRead_, handleWrite_;

    int handleEvent();

    int getFd();

    // epoll 事件管理
    int del();
    int regist();
    int enableReading();
    int enableWriting();
    int disableReading();
    int disableWriting();

    int setCallBack(ChannelCallBack handleRead, ChannelCallBack handleWrite);
};

} // namespace net
} // namespace ndsl

#endif // __BASECHANNEL_H__