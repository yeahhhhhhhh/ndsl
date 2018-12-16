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
    // epoll事件注册 FIXME: 看看什么时候注册这个比较好
    int regist();
    int update();
    int del();
    ChannelCallBack *pCb_;

  public:
    uint32_t getRevents();
    int setRevents(uint32_t revents);
    uint32_t getEvents();
    EventLoop *getEventLoop();

    int handleEvent();

    // epoll 事件管理
    int enableReading();
    int enableWriting();
    int disableReading();
    int disableWriting();

    int setCallBack(ChannelCallBack *pCb);
};

} // namespace net
} // namespace ndsl

#endif // __BASECHANNEL_H__