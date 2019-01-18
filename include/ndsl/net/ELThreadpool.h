/**
 * @file ELThreadpool.h
 * @brief
 * 封装EventLoop的线程和线程池
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#ifndef __NDSL_UTILS_EVENTLOOPTHREAD_H__
#define __NDSL_UTILS_EVENTLOOPTHREAD_H__
#include <pthread.h>
#include <vector>
#include "ndsl/utils/Noncopyable.h"

namespace ndsl {

namespace net {
class EventLoop;

// 线程类
class Thread
    : public utils::noncopyable
    , public utils::nonmoveable
{
  public:
    using ThreadFunc = void *(*) (void *); // 线程函数

  private:
    ThreadFunc func_; // 线程函数
    void *param_;     // 函数参数
    pthread_t id_;    // 线程id
    void *ret_;       // 线程返回值

  public:
    Thread(ThreadFunc threadfunc, void *param);
    ~Thread();

    // 开启线程
    int run();
    // 等待线程结束
    int join(void **retval = NULL);
    // CPU核心数
    static int getNumberOfProcessors();

  private:
    static void *runInThread(void *);
};

// EventLoop线程类
class ELThread
    : public utils::noncopyable
    , public utils::nonmoveable
{
  private:
    EventLoop *loop_; // 记录线程中的loop
    Thread thread_;   // 线程
    bool running_;    // 标志线程是否在使用

  public:
    ELThread(EventLoop *loop);
    ~ELThread();

    // 启动线程
    int run();
    // 等待线程结束
    int join();
    // 线程是否正在运行
    bool isRunning() const;
};

// EventLoop线程池
class ELThreadpool
    : public utils::noncopyable
    , public utils::nonmoveable
{
  private:
    std::vector<ELThread *> loopThreads_; // 线程池中的所有线程
    std::vector<EventLoop *> loops_;      // 线程池中所有的EventLoop

    // 线程池容量与CPU物理核心的倍数
    static const int Redundancy = 2;
    // 最大线程数 默认为两倍的CPU核心数
    unsigned int MaxThreads_;
    // 当前线程指向
    unsigned int nextThread_;

  public:
    ELThreadpool();
    ~ELThreadpool();

    // 初始化线程池
    int start();
    // 获取EventLoop
    EventLoop *getNextEventLoop();

    // 设置最大线程数
    int setMaxThreads(unsigned int maxThreads);
    // 获取最大线程数
    unsigned int getMaxThreads() const;

    // 关闭线程池中所有线程
    int quit();
    // 已有EventLoop数量
    int getLoopsNum();

  private:
    int capacity(); // 默认最大线程数
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_UTILS_EVENTLOOPTHREAD_H__