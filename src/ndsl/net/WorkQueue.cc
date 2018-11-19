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
    queueMutex_.lock();
    bool ret = queue_.empty();
    queueMutex_.unlock();
    return ret;
}

void WorkQueue::doit()
{
    work_struct *curWork;

    // 取队首任务
    queueMutex_.lock();
    // 若为空，则退出
    if (queue_.empty()) {
        queueMutex_.unlock();
        return;
    }
    curWork = queue_.front(); // 若非空，则取出
    queueMutex_.unlock();

    // 执行任务
    curWork->doit(curWork->para);
}

void WorkQueue::enQueue(work_struct *work)
{
    queueMutex_.lock();
    queue_.push(work);
    queueMutex_.unlock();
}

} // namespace net
} // namespace ndsl
