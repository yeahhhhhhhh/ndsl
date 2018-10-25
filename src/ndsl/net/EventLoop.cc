/*
 * @file: EventLoop.cc
 * @brief
 * 事件循环的实现
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include "ndsl/net/Channel.h"
#include "ndsl/net/EventLoop.h"

namespace ndsl {

namespace net {
EventLoop::EventLoop(Epoll epoll)
    : epoll_(epoll)
{}

EventLoop::~EventLoop() {}

int EventLoop::loop()
{
    quit_ = false;

    // 进入事件循环
    while (!quit_) {
        std::vector<Channel *> channels;
        epoll_.wait(channels);

        // 处理事件
        for (auto it = channels.begin(); it != channels.end(); ++it) {
            (*it)->handleEvent();
        }
    }
}

int EventLoop::regist(Channel *pCh) { return epoll_.regist(pCh); }

int EventLoop::update(Channel *pCh) { return epoll_.update(pCh); }

int EventLoop::del(Channel *pCh) { return epoll_.del(pCh); }

int EventLoop::quit() { quit_ = true; }

} // namespace net
} // namespace ndsl