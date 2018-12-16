/**
 * @file CallbackIoChannel.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */

#ifndef __CALLBACKIOCHANNEL__
#define __CALLBACKIOCHANNEL__
#include "Channel.h"
#include "EventLoop.h"

class CallbackIoChannel : public Channel
{
  private:
    int sockFd_;
    void *buf_;
    size_t len_;
    int flag_;
    Callback cb_;
    void *param_;
    EventLoop pLoop_;

  public:
    int getEventLoop();
    uint32_t getRevents();
    int handleEvent();
    int getFd();
    int regist();

    // epoll 管理
    int enableReading();
    int enableWriting();
    int disableWriting();
    int update();

    int handleRead();
    int handleWrite();
};

#endif // __CALLBACKIOCHANNEL__