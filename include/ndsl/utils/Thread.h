/**
 * @file Thread.h
 * @brief
 * 封装线程类
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#ifndef __NDSL_UTILS_THREAD_H__
#define __NDSL_UTILS_THREAD_H__

#include "../config.h"
#include <vector>
#include <list>
#include <mutex>
#include <pthread.h>
#include <condition_variable>
#include "ndsl/utils/Noncopyable.h"

namespace ndsl {
namespace utils {

using ThreadFunc = void *(*) (void *); // 线程函数

class Thread
    : public noncopyable
    , public nonmoveable
{
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

class Threadpool
    : public noncopyable
    , public nonmoveable
{
  private:
    std::vector<Thread *> pool_; // 线程池中的线程

    // 线程池容量与CPU物理核心的倍数
    static const int Redundancy = 2;

  public:
    Threadpool();
    ~Threadpool();

    // 创建一个线程
    int create(ThreadFunc threadfunc, void *param);
    // 等待所有线程结束
    int join();

    int capacity(); // 线程池容量
    int size();     // 当前线程池使用的大小

  private:
    // 清除线程池中的所有线程
    int clean();
};
} // namespace utils
} // namespace ndsl

#endif // __NDSL_UTILS_THREAD_H__