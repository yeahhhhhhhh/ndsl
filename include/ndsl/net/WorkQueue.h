/*
 * @file: WorkQueue.h
 * @brief
 * 任务队列
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_WORKQUEUE_H__
#define __NDSL_NET_WORKQUEUE_H__

#include <queue>
#include <mutex>

namespace ndsl {
namespace net {

// 定义work结构体
struct work_struct
{
    // 任务回调函数
    using Callback = void (*)(void *);
    Callback doit; // 回调函数
    void *para;    // 回调函数的参数指针
};

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

} // namespace net
} // namespace ndsl
#endif // __NDSL_NET_WORKQUEUE_H__