/**
 * @file TimeWheel.h
 * @brief
 * TimeWheel为事件管理提供时间依据
 * TimerfdChannel便于TimeWheel使用EventLoop
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_TIMEWHEEL_H__
#define __NDSL_NET_TIMEWHEEL_H__

#include <sys/timerfd.h>
#include <list>
#include "ndsl/net/Channel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace net {

class TimerfdChannel : public Channel
{
  private:
    int fd_;
    uint32_t events_;
    uint32_t revents_;
    EventLoop *pLoop_;

  public:
    TimerfdChannel(int fd, EventLoop *loop);
    ~TimerfdChannel();

    // 回调
    int onRead(char *inBuf);
    int onWrite();

    int getFd();
    uint32_t getRevents();
    int setRevents(uint32_t revents);
    uint32_t getEvents();
    EventLoop *getEventLoop();

    int handleEvent();

    // epoll 事件管理
    int enableReading();
    int enableWriting();
    int disableWriting();
    int isWriting();

  private:
    // epoll事件注册
    int update();
    int regist();
    int del();
};

class TimerWheel
{
  public:
    struct task
    {
        using Taskfunc = void (*)(void *);
        int interval;  // 时间间隔
        int times;     // 0:无限制响应   1:响应次数
        int circle;    // 每几个周期响应一次
        Taskfunc doit; // 函数指针
        void *para;    // 函数参数
    };

  private:
    EventLoop *pLoop_;
    TimerfdChannel *ptimerfdChannel_;
    long intervalMs_; // 时间间隔,以微秒为单位
    int slotNum_;     // 时间刻度个数
    int tick_;
    std::list<std::list *> slot;

  public:
    TimerWheel(EventLoop *loop, long intervalMs, int slotNum);
    ~TimerWheel();

    int init();  // 初始化TimerfdChannel
    int start(); // 开始运行时间轮
    int stop();  // 停止运行时间轮

    int addTask();    // 增加新任务
    int removeTask(); // 删除任务
    int updateTask(); // 更新任务

    int tickHandler(); // 处理事件
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_TIMERFDCHANNEL_H__