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
    int fd_; // sockfd

    void *pThis_; // 存储上层的this Connecion Accept

    // 定义handleRead handleWrite函数指针原型
    using ChannelCallBack = int (*)(void *);

  public:
    BaseChannel(int fd, EventLoop *loop);
    // ~BaseChannel(); // TODO: 要不要去做fd的释放

    // 指向被调用的函数
    ChannelCallBack handleRead_, handleWrite_;

    int handleEvent();
    int getFd();

    // epoll 事件管理
    int erase();
    int enroll(bool isET);

    // 内部使用 ps.留给EVentLoop
    int enrollIn(bool isET);

    // 设置回调函数和上层指针
    int setCallBack(
        ChannelCallBack handleRead,
        ChannelCallBack handleWrite,
        void *thi);
};

} // namespace net
} // namespace ndsl

#endif // __BASECHANNEL_H__