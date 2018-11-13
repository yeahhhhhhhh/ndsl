/*
 * @file: WorkQueue.cc
 * @brief
 * 实现任务队列
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include "ndsl/net/WorkQueue.h"

namespace ndsl {
namespace net {
bool WorkQueue::empty()
{
    workQueueMutex_.lock();
    bool ret = workQueue_.empty();
    workQueueMutex_.unlock();
    return ret;
}

void WorkQueue::doit()
{
    work_struct *curWork;

    // 取队首任务
    workQueueMutex_.lock();
    // 若为空，则退出
    if (workQueue_.empty()) {
        workQueueMutex_.unlock();
        return;
    }
    curWork = workQueue_.front(); // 若非空，则取出
    workQueueMutex_.unlock();

    // 执行任务
    curWork->doit(curWork->para);
}

void WorkQueue::enQueue(work_struct *work)
{
    workQueueMutex_.lock();
    workQueue_.push(work);
    workQueueMutex_.unlock();
}

} // namespace net
} // namespace ndsl
