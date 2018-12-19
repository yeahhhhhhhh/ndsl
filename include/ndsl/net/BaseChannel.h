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
    int update();

    ChannelCallBack *pCb_;

  public:
    BaseChannel(int fd, EventLoop *loop);

    int handleEvent();

    int getFd();

    // epoll 事件管理
    int del();
    int regist();
    int enableReading();
    int enableWriting();
    int disableReading();
    int disableWriting();
    int changeMode2ET();
    int changeMode2LT();

    int setCallBack(ChannelCallBack *pCb);
};

} // namespace net
} // namespace ndsl

#endif // __BASECHANNEL_H__