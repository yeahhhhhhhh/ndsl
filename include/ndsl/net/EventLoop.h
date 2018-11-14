/*
 * @file: EventLoop.h
 * @brief
 * 事件循环的封装
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_EVENTLOOP_H__
#define __NDSL_NET_EVENTLOOP_H__

// #include "ndsl/net/Channel.h"
#include "ndsl/net/InterruptChannel.h"
// #include "ndsl/net/Epoll.h"
#include "ndsl/net/WorkQueue.h"

namespace ndsl {
namespace net {

class Epoll;
class Channel;
class WorkQueue;
class InterruptChannel;

class EventLoop
{
  private:
    WorkQueue *workqueue_; // 任务队列
    Epoll *epoll_;
    InterruptChannel *pIntrCh_; // 用于中断的channel

  public:
    EventLoop(Epoll *epoll);
    ~EventLoop();

    // 初始化中断器
    int init();

    // 开始循环
    void loop();
    // 退出循环
    // int quit();

    // 添加任务
    void addWork(work_struct *work);

    // 注册、更新、删除事件
    int regist(Channel *);
    int update(Channel *);
    int del(Channel *);

  private:
    void interrupter();
};

} // namespace net

} // namespace ndsl

#endif // __NDSL_NET_EVENTLOOP_H__