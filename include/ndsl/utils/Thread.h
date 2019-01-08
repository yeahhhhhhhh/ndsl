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

class Thread : public noncopyable
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

    int run();
    int join(void **retval);

  private:
    static void *runInThread(void *);
};

class Threadpool
{
  private:
    std::mutex queueMutex_;             // 任务队列的互斥量
    std::condition_variable condEmpty_; // 任务队列的非空的条件变量
    // std::condition_variable condFull_;  // 任务队列满的条件变量

    std::list<Thread::ThreadFunc> taskQueue_; // 任务队列
    std::vector<Thread *> threads_;           // 线程池中的线程

    size_t threadNum_;

  public:
    Threadpool(size_t threadNum);
    ~Threadpool();
};

Threadpool::Threadpool(size_t threadNum)
    : threadNum_(threadNum)
{}

Threadpool::~Threadpool() {}

} // namespace utils
} // namespace ndsl

#endif // __NDSL_UTILS_THREAD_H__