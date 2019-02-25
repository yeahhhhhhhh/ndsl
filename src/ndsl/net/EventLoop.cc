/**
 * @file EventLoop.cc
 * @brief
 * 事件循环的实现
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include <errno.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include "ndsl/net/Epoll.h"
#include "ndsl/net/Channel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/Log.h"

namespace ndsl {
namespace net {

/**
 * @class EventLoop
 * @brief
 * 事件循环: 包含一个QueueChannel和一个InterruptChannel
 */
EventLoop::EventLoop()
    : pQueCh_(NULL)
    , pIntrCh_(NULL)

{}

EventLoop::~EventLoop()
{
    if (pIntrCh_) { delete pIntrCh_; } // 若pIntrCh_不为空,则释放内存
    if (pQueCh_) { delete pQueCh_; }   // 若pQueCh_不为空,则释放内存
}

int EventLoop::init()
{
    int evfd;
    int ret;

    // 初始化epoll
    ret = epoll_.init();
    if (ret != S_OK) { return ret; }

    // 若pQueCh_为空,则分配eventfd
    if (!pQueCh_) {
        evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LOG_ERROR_LEVEL,
                LOG_SOURCE_EVENTLOOP,
                "pQueCh_ eventfd errno = %d:%s\n",
                errno,
                strerror(errno));
            return errno;
        }

        // 创建QueueChannel
        pQueCh_ = new QueueChannel(evfd, this);

        // 设置回调函数
        pQueCh_->setCallBack(pQueCh_->onQueue, NULL, pQueCh_);
        ret = pQueCh_->enrollIn(false);
        if (ret != S_OK) return ret; // 若不成功直接返回
    }

    // 若pIntrCh_为空,则分配eventfd
    if (!pIntrCh_) {
        evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LOG_ERROR_LEVEL,
                LOG_SOURCE_EVENTLOOP,
                "pIntrCh_ eventfd errno = %d:%s\n",
                errno,
                strerror(errno));
            return errno;
        }

        // 创建InterruptChannel
        pIntrCh_ = new InterruptChannel(evfd, this);
        ret = pIntrCh_->enrollIn(false);
        if (ret != S_OK) return ret; // 若不成功直接返回
    }
    return S_OK;
}

void *EventLoop::loop(void *pThis)
{
    EventLoop *el = reinterpret_cast<EventLoop *>(pThis);
    int nEvents = 0;
    // 进入事件循环
    while (true) {
        Channel *channels[Epoll::MAX_EVENTS];
        if (S_OK != el->epoll_.wait(channels, nEvents, -1)) {
            return (void *) S_FALSE; // 若wait出错,则直接返回
        }

        bool quit = false;    // 退出标志
        bool haswork = false; // 中断标志

        // 处理事件
        for (int i = 0; i < nEvents; i++) {
            if (el->pIntrCh_ == channels[i]) // 退出Channel响应,退出标记
                quit = true;
            else if (el->pQueCh_ == channels[i]) // 任务队列非空,中断标记
                haswork = true;
            else
                channels[i]->handleEvent();
        }

        // 处理任务队列
        if (haswork) {
            uint64_t data;
            read(el->pQueCh_->getFd(), &data, sizeof data);
            el->pQueCh_->handleEvent();
        }
        // 退出
        if (quit) {
            uint64_t data;
            read(el->pIntrCh_->getFd(), &data, sizeof data);
            LOG(LOG_DEBUG_LEVEL, LOG_SOURCE_EVENTLOOP, "quit");
            break;
        }
    }
    return S_OK;
}

// 添加任务
int EventLoop::addWork(WorkItem *item)
{
    pQueCh_->addWork(item);
    int ret = pQueCh_->onWrite();
    return ret;
}

// 删除任务
int EventLoop::removeWork(WorkItem *item) { return pQueCh_->removeWork(item); }

int EventLoop::enroll(Channel *pCh) { return epoll_.enroll(pCh); }

int EventLoop::modify(Channel *pCh) { return epoll_.modify(pCh); }

int EventLoop::erase(Channel *pCh) { return epoll_.erase(pCh); }

void EventLoop::quit() { pIntrCh_->onWrite(); }

} // namespace net
} // namespace ndsl