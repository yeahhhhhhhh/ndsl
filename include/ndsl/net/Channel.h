/**
 * @file Channel.h
 * @brief
 * Channel 基类
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __NDSL_NET_CHANNEL_H__
#define __NDSL_NET_CHANNEL_H__
// #include "EventLoop.h"
#include <stdint.h>
#include "ndsl/utils/temp_define.h"

#include <cstdio>

namespace ndsl {
namespace net {

class EventLoop;

// class ChannelCallBack
// {
//   public:
//     using Callback = void (*)(void *); // Callback 函数指针原型

//     virtual int handleRead() = 0;
//     virtual int handleWrite() = 0;
// };

struct Channel
{
  public:
    using Callback = void (*)(void *); // Callback 函数指针原型

    // TODO: 是否改为protected 有待商榷
  private:
    uint32_t events_;  // 注册事件
    uint32_t revents_; // 发生事件
    EventLoop *pLoop_; // 指向EventLoop

  public:
    Channel(EventLoop *loop)
        : pLoop_(loop)
        , events_(0)
        , revents_(0)
    {}
    Channel() {}
    virtual ~Channel() {} // 虚析构函数

    EventLoop *getEventLoop() { return pLoop_; }
    uint32_t getRevents() { return revents_; }

    int setRevents(uint32_t revents)
    {
        revents_ = revents;
        return S_OK;
    }

    uint32_t getEvents() { return events_; }

    int setEvents(uint32_t events)
    {
        events_ = events;
        return S_OK;
    }

    virtual int handleEvent() = 0; // loop的事件处理函数
    virtual int getFd() = 0;       // rdma的fd在结构内部
};

} // namespace net
} // namespace ndsl

#endif // __CHANNEL_H__
