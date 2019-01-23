/**
 * @file EventLoop.h
 * @brief
 * 事件循环的封装
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#ifndef __NDSL_NET_EVENTLOOP_H__
#define __NDSL_NET_EVENTLOOP_H__

#include <list>
#include <mutex>
#include <unistd.h>
#include "ndsl/utils/Log.h"
#include "ndsl/utils/Error.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/BaseChannel.h"

namespace ndsl {
namespace net {

/**
 * @class EventLoop
 * @brief
 * 事件循环: 包含一个QueueChannel和一个InterruptChannel
 */
class EventLoop
{
  public:
    // 定义work结构体
    // FIXME:堆上分配内存,最终会在WorkQueue中释放
    struct WorkItem
    {
        // 任务回调函数
        using Callback = void (*)(void *);
        Callback doit; // 回调函数
        void *param;   // 回调函数的参数指针
    };

  private:
    /**
     * @class QueueChannel
     * @brief
     * 用于维护任务队列
     */
    class QueueChannel : public BaseChannel
    {
      private:
        /**
         * @brief
         * 任务队列
         */
        class WorkQueue
        {
          private:
            std::list<WorkItem *> queue_; // 任务队列,用list实现
            std::mutex queueMutex_;       // 任务队列的锁

          public:
            // 队列是否为空
            bool empty()
            {
                queueMutex_.lock();
                bool ret = queue_.empty();
                queueMutex_.unlock();
                return ret;
            }
            // 执行队头任务
            void doit()
            {
                WorkItem *curWork;

                std::list<struct WorkItem *> getQueue;

                queueMutex_.lock();
                getQueue.swap(queue_);
                queueMutex_.unlock();

                while (!getQueue.empty()) {
                    // 取队首任务
                    curWork = getQueue.front(); // 若非空，则取出
                    getQueue.pop_front();       // 删除第一个元素

                    // 执行任务
                    curWork->doit(curWork->param);

                    // TODO:在此处释放WorkItem
                    delete curWork;
                }
            }
            // 返回队列长度
            size_t size() { return queue_.size(); }
            // 队尾增加任务
            int enqueue(WorkItem *item)
            {
                queueMutex_.lock();
                queue_.push_back(item);
                queueMutex_.unlock();
                return S_OK;
            }
            // 删除队中任务
            int dequeue(WorkItem *item)
            {
                queueMutex_.lock();
                for (auto it = queue_.begin(); it != queue_.end(); ++it) {
                    if ((*it) == item) {
                        queue_.erase(it);
                        queueMutex_.unlock();
                        return S_OK;
                    }
                }
                queueMutex_.unlock();
                return S_FALSE;
            }
        };

      private:
        WorkQueue workqueue_; // 任务队列

      public:
        QueueChannel(int fd, EventLoop *loop)
            : BaseChannel(fd, loop)
        {}
        ~QueueChannel()
        {
            // 关闭描述符
            if (getFd() >= 0) {
                erase(); // 从EventLoop中取消注册
                ::close(getFd());
            }
        }

        // 增加任务
        int addWork(WorkItem *item) { return workqueue_.enqueue(item); }

        // 删除任务
        int removeWork(WorkItem *item) { return workqueue_.dequeue(item); }

        // 发送中断信号
        int onWrite()
        {
            uint64_t data = 1;
            int ret = ::write(getFd(), &data, sizeof(data));

            if (ret == -1) {
                LOG(LOG_ERROR_LEVEL,
                    LOG_SOURCE_EVENTLOOP,
                    "QueueChannel::onWrite write errno = %d:%s\n",
                    errno,
                    strerror(errno));
                return errno;
            }

            return S_OK;
        }
        // 处理队列中的任务
        static int onQueue(void *pThis)
        {
            QueueChannel *pQc = (QueueChannel *) pThis;
            while (!pQc->workqueue_.empty()) {
                pQc->workqueue_.doit();
            }
            return S_OK;
        }
    };
    /**
     * @class InterruptChannel
     * @brief
     * 中断EventLoop,退出循环
     */
    class InterruptChannel : public BaseChannel
    {
      private:
        EventLoop *loop_;

      public:
        InterruptChannel(int fd, EventLoop *loop)
            : BaseChannel(fd, loop)
        {}
        ~InterruptChannel()
        {
            if (getFd() >= 0) {
                erase(); // 从EventLoop中取消注册
                ::close(getFd());
            }
        }

        // 发送中断信号
        int onWrite()
        {
            uint64_t data;
            data = 1;

            int ret = ::write(getFd(), &data, sizeof(data));

            if (ret == -1) {
                LOG(LOG_ERROR_LEVEL,
                    LOG_SOURCE_EVENTLOOP,
                    "InterruptChannel::onWrite write errno = %d:%s\n",
                    errno,
                    strerror(errno));
                return errno;
            }

            return S_OK;
        }
    };

  private:
    Epoll epoll_;               // 用于监听事件
    QueueChannel *pQueCh_;      // 用于维护任务队列的Channel
    InterruptChannel *pIntrCh_; // 用于退出的channel

  public:
    EventLoop();
    ~EventLoop();

    // 初始化中断器
    int init();

    // 开始循环
    static void *loop(void *pThis);

    // 添加任务
    int addWork(WorkItem *item);
    int removeWork(WorkItem *item);

    // 注册、更新、删除事件
    int enroll(Channel *);
    int modify(Channel *);
    int erase(Channel *);

    // 退出
    void quit();
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_EVENTLOOP_H__