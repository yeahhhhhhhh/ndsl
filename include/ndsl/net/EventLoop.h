/*
 * @file: EventLoop.h
 * @brief
 * 事件循环的封装
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_EVENTLOOP_H__
#define __NDSL_NET_EVENTLOOP_H__

#include <queue>
#include <mutex>

// #include "ndsl/net/Channel.h"
// #include "ndsl/net/InterruptChannel.h"
// #include "ndsl/net/Epoll.h"
// #include "ndsl/net/WorkQueue.h"

namespace ndsl {
namespace net {

// struct work_struct;
class Epoll;
class Channel;
// class InterruptChannel;

// 定义work结构体
struct work_struct
{
    // 任务回调函数
    using Callback = void (*)(void *);
    Callback doit; // 回调函数
    void *para;    // 回调函数的参数指针
};

/**
 * @brief:
 * 任务队列
 */
class WorkQueue
{
  private:
    std::queue<work_struct *> queue_; // 任务队列
    std::mutex queueMutex_;           // 任务队列的锁

  public:
    // WorkQueue(/* args */);
    // ~WorkQueue();

    // 队列是否为空
    bool empty();
    // 执行队头任务
    void doit();
    // 队尾增加任务
    void enQueue(work_struct *work);
};

/**
 * @class: QueueChannel
 * @brief:
 * 维护任务队列
 */
class QueueChannel : public Channel
{
  private:
    WorkQueue *workqueue_; // 任务队列
  public:
    QueueChannel(int fd, EventLoop *loop);
    ~QueueChannel();

    // 增加任务
    void addWork(work_struct *work);
    // 没有重载
    int onRead();
    // 发送中断信号
    int onWrite();
    // 处理队列中的任务
    int handleEvent();
};

/**
 * @class: InterruptChannel
 * @brief: 中断EventLoop,退出循环
 */

class InterruptChannel : public Channel
{
  private:
    /* data */
  public:
    InterruptChannel(int fd, EventLoop *loop);
    ~InterruptChannel();

    // 没有重载
    int onRead();
    // 发送中断信号
    int onWrite();
    // 没有重载
    int handleEvent();
};

/**
 * @class: EventLoop
 * @brief:
 * 事件循环: 包含一个QueueChannel和一个InterruptChannel
 */
class EventLoop
{
  private:
    Epoll *epoll_;
    QueueChannel *pQueCh_;      // 用于维护任务队列的Channel
    InterruptChannel *pIntrCh_; // 用于中断的channel

  public:
    EventLoop(Epoll *epoll);
    ~EventLoop();

    // 初始化中断器
    int init();

    // 开始循环
    int loop();

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