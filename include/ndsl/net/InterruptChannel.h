/*
 * @file: InterruptChannel.h
 * @brief
 * 中断eventloop的channel
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_INTERRUPTCHANNEL_H__
#define __NDSL_NET_INTERRUPTCHANNEL_H__

#include "ndsl/net/Channel.h"
#include "ndsl/net/EventLoop.h"

namespace ndsl {
namespace net {

class EventLoop;

class InterruptChannel : public Channel
{
  private:
    /* data */
  public:
    InterruptChannel(int fd, EventLoop *loop);

    int onRead();
    int onWrite();
    int handleEvent();
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_INTERRUPTCHANNEL_H__