// #include "ndsl/net/Channel.h"
// #include "ndsl/net/Epoll.h"
// #include "ndsl/net/EventLoop.h"

// namespace ndsl {
// namespace net {

// Channel::Channel(int fd, EventLoop *loop)
//     : fd_(fd)
//     , pLoop_(loop)
// {}

// Channel::~Channel() {}

// int Channel::getFd() { return fd_; }

// void Channel::setRevents(int revents) { revents_ = revents; }

// int Channel::getRevents() { return revents_; }

// EventLoop *Channel::getEventLoop() { return pLoop_; }

// int Channel::getEvents() { return events_; }

// void Channel::enableReading()
// {
//     events_ |= EPOLLIN;
//     events_ |= EPOLLET;
//     regist();
// }

// void Channel::enableWriting()
// {
//     events_ |= EPOLLOUT;
//     update();
// }

// void Channel::disableWriting()
// {
//     events_ &= ~EPOLLOUT;
//     update();
// }

// int Channel::isWriting() { return events_ & EPOLLOUT; }

// int Channel::update() { return getEventLoop()->update(this); }

// int Channel::regist() { return getEventLoop()->regist(this); }

// int Channel::del() { return -1; }

// } // namespace net
// } // namespace ndsl
