/*
 * @file: EventLoop.cc
 * @brief
 * 事件循环的实现
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <sys/eventfd.h>
#include <errno.h>
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/Channel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/WorkQueue.h"

namespace ndsl {
namespace net {
EventLoop::EventLoop(Epoll *epoll)
    : epoll_(epoll)
    , pIntrCh_(NULL)
{}

EventLoop::~EventLoop()
{
    // 若evfd存在，则关闭
    if (pIntrCh_) { delete pIntrCh_; }
}

int EventLoop::init()
{
    int evfd;
    if (pIntrCh_ == NULL) {
        evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LEVEL_ERROR, "EventLoop::init eventfd\n");
            return errno;
        }

        // 创建中断channel
        pIntrCh_ = new InterruptChannel(evfd, this);
        regist(pIntrCh_);

        return S_OK;
    }

    return S_FAIL;
}

void EventLoop::loop()
{
    // 进入事件循环
    while (true) {
        std::vector<Channel *> channels;
        epoll_->wait(channels);

        int interrupt = false;

        // 处理事件
        for (auto it = channels.begin(); it != channels.end(); ++it) {
            // 若任务队列非空，则标记中断
            if (pIntrCh_->getFd() == (*it)->getFd())
                interrupt = true;
            else
                (*it)->handleEvent();
        }

        if (interrupt) {
            while (!workqueue_->empty()) {
                workqueue_->doit();
            }
        }
    };
    // return S_OK;
}

// 添加任务
void EventLoop::addWork(work_struct *work)
{
    workqueue_->enQueue(work);
    interrupter();
}

int EventLoop::regist(Channel *pCh) { return epoll_->regist(pCh); }

int EventLoop::update(Channel *pCh) { return epoll_->update(pCh); }

int EventLoop::del(Channel *pCh) { return epoll_->del(pCh); }

void EventLoop::interrupter() { pIntrCh_->onWrite(); }

} // namespace net
} // namespace ndsl