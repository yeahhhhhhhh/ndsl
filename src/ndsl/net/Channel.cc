#include "ndsl/net/Channel.h"

namespace ndsl {
namespace net {

Channel::Channel(int fd, EventLoop *loop)
    : fd_(fd)
    , pLoop_(loop)
{}

int Channel::getFd() { return fd_; }

int Channel::setRevents(int revents) { revents_ = revents; }

int Channel::getRevents() { return revents_; }

EventLoop *Channel::getEventLoop() { return pLoop_; }

int Channel::getEvents() { return events_; }

int Channel::enableReading()
{
    events_ |= EPOLLIN;
    regist();
}

int Channel::enableWriting()
{
    events_ |= EPOLLOUT;
    update();
}

int Channel::disableWriting()
{
    events_ &= ~EPOLLOUT;
    update();
}

int Channel::isWriting() { return events_ & EPOLLOUT; }

int Channel::update() { getEventLoop()->update(this); }

int Channel::regist() { getEventLoop()->regist(this); }

int Channel::del() {}

} // namespace net
} // namespace ndsl
