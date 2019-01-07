/*
 * File: ChannelCallBack.h
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Thursday, 29th November 2018 9:58:09 am
 */

#ifndef __CHANNELCALLBACK__
#define __CHANNELCALLBACK__

namespace ndsl {
namespace net {

class ChannelCallBack
{
  public:
    virtual int handleRead() = 0;
    virtual int handleWrite() = 0;
};

} // namespace net
} // namespace ndsl

#endif // __CHANNELCALLBACK__