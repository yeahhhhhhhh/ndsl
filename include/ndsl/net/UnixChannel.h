////
// @file UnixChannel
// @brief
// fengzhuang channle class
//
// @author ranxiangjun
// @email ranxianshen@gmail.com
//
#ifndef __UNIXCHANNEL_H__
#define __UNIXCHANNEL_H__
#include "BaseChannel.h"

namespace ndsl {
namespace net {

class UnixConnection;
class EventLoop;

class UnixChannel : public BaseChannel
{
  public:
    UnixChannel(int sockfd, EventLoop *loop);
    ~UnixChannel();

    UnixConnection *newConnection(int connfd);
};

} // namespace net
} // namespace ndsl

#endif // __UNIXCHANNEL_H__
