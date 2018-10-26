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
#include "ndsl/utils/Interrupter.h"

namespace ndsl {

namespace net {
EventLoop::EventLoop(Epoll *epoll)
    : epoll_(epoll)
    , intr_(NULL)
{}

EventLoop::~EventLoop()
{
    if (intr_) {
        ::close(intr_->getFd());
        delete intr_;
    }
}

int EventLoop::init()
{
    if (intr_ == NULL) {
        int evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LEVEL_ERROR, "EventLoop::init eventfd\n");
            return errno;
        }

        intr_ = new utils::Interrupter(this, evfd);

        return intr_.regist();
    }

    return S_FAIL;
}

int EventLoop::loop()
{
    quit_ = false;

    // 进入事件循环
    while (!quit_) {
        std::vector<Channel *> channels;
        epoll_->wait(channels);

        // 处理事件
        for (auto it = channels.begin(); it != channels.end(); ++it) {
            (*it)->handleEvent();
        }
    }

    if (quit_) return S_FAIL;
    return S_OK;
}

int EventLoop::regist(Channel *pCh) { return epoll_->regist(pCh); }

int EventLoop::update(Channel *pCh) { return epoll_->update(pCh); }

int EventLoop::del(Channel *pCh) { return epoll_->del(pCh); }

int EventLoop::quit() { return intr_->interrupt(); }

} // namespace net
} // namespace ndsl