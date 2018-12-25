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

    // 存储上层的this
    void *pThis_;

    using ChannelCallBack =
        int (*)(void *); // 定义handleRead handleWrite函数指针原型

  public:
    BaseChannel(int fd, EventLoop *loop);
    // ~BaseChannel(); // TODO: 要不要去做fd的释放

    // 指向被调用的函数
    ChannelCallBack handleRead_, handleWrite_;

    int handleEvent();
    int getFd();

    // epoll 事件管理
    // TODO: 改名字
    int del();
    int regist(bool isET);
    int enableReading();
    int enableWriting();
    int disableReading();
    int disableWriting();

    int setCallBack(
        ChannelCallBack handleRead,
        ChannelCallBack handleWrite,
        void *thi);
};

} // namespace net
} // namespace ndsl

#endif // __BASECHANNEL_H__