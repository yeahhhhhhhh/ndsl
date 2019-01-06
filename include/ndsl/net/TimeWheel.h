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
#include "ndsl/net/BaseChannel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace net {

class TimerfdChannel : public BaseChannel
{
    // FIXME:使用BaseChannel的问题
    // 1.使用Callback类,还是使用函数指针?
    // (用Callback(handleEvent不方便),个人认为使用using更加方便)
    // 2.缺少头文件(S_OK)
    // 3.EventLoop提供ET/LT转换,还是Channel自己去更新?(调用顺序?regist时指定?)

    // private:
    //   int fd_;
    //   uint32_t events_;
    //   uint32_t revents_;
    //   EventLoop *pLoop_;

  public:
    TimerfdChannel(int fd, EventLoop *loop);
    ~TimerfdChannel();

    // 回调
    // int onRead(char *inBuf);
    // int onWrite();

    // int getFd();
    // uint32_t getRevents();
    // int setRevents(uint32_t revents);
    // uint32_t getEvents();
    // EventLoop *getEventLoop();

    // int handleEvent();

    // // epoll 事件管理
    // int enableReading();
    // int enableWriting();
    // int disableWriting();
    // int isWriting();

  private:
    // epoll事件注册
    // int update();
    // int regist();
    // int del();
};

class TimeWheel
{
  public:
    struct Task
    {
        using Taskfunc = void (*)(void *);
        int setInterval = -1;  // 设置的时间间隔
        int restInterval = -1; // 剩余时间间隔(不由用户设置)
        int setTick = -1; // 记录放在哪个slot位置上(不由用户设置)
        int times = 1;    // -1:无限制响应   1:响应次数
        Taskfunc doit;    // 函数指针
        void *para;       // 函数参数
    };
    // 转一圈需要1min,一共有60个槽,两个槽之间间隙为1s
    static const int SLOTNUM = 60; // 一共有60个时间槽
    static const int INTERVAL = 1; // 每两个槽之间的间隔为1s

  private:
    int curTick_;                     // 指示当前刻度
    EventLoop *pLoop_;                // TimerfdChannel注册的eventloop
    TimerfdChannel *ptimerfdChannel_; // 注册在epoll上的channel
    std::list<Task *> slot_[SLOTNUM]; // 每个刻度上的任务队列(双向链表)

  public:
    TimeWheel(EventLoop *loop);
    ~TimeWheel();

    int init();  // 初始化TimerfdChannel和slot
    int start(); // 开始运行时间轮
    int stop();  // 停止运行时间轮

    int addTask(Task *Task);    // 增加新任务
    int removeTask(Task *task); // 删除任务

    static int onTick(void *pThis); // 处理事件
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_TIMEWHEEL_H__