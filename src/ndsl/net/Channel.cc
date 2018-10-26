#include "ndsl/net/Channel.h"

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
    register();
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

int TcpChannel::isWriting() { return events_ & EPOLLOUT; }
