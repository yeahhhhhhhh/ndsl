/**
 * @file TimerfdChannel.h
 * @brief
 * timerfd,为事件管理提供时间参考
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_TIMERFDCHANNEL_H__
#define __NDSL_NET_TIMERFDCHANNEL_H__

#include "ndsl/net/Channel.h"

namespace ndsl {
namespace net {

class TimerfdChannel : public Channel
{
  private:
    /* data */
  public:
    TimerfdChannel(/* args */);
    ~TimerfdChannel();
};

TimerfdChannel::TimerfdChannel(/* args */) {}

TimerfdChannel::~TimerfdChannel() {}
} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_TIMERFDCHANNEL_H__