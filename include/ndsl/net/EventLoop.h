/*
 * @file: EventLoop.h
 * @brief
 * 事件循环的封装
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_EVENTLOOP_H__
#define __NDSL_NET_EVENTLOOP_H__

#include "ndsl/net/Epoll.h"
#include "ndsl/utils/Interrupter.h"

namespace ndsl {
namespace net {

class Epoll;
class Channel;

class EventLoop
{
  private:
    Epoll *epoll_;
    utils::Interrupter *intr_;
    bool quit_;

  public:
    EventLoop(Epoll *epoll);
    ~EventLoop();

    // 初始化中断器
    int init();

    // 开始循环
    int loop();
    // 退出循环
    int quit();

    // 注册、更新、删除事件
    int regist(Channel *);
    int update(Channel *);
    int del(Channel *);
};

} // namespace net

} // namespace ndsl

#endif // __NDSL_NET_EVENTLOOP_H__