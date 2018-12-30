/**
 * @file BaseChannel.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/BaseChannel.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/EventLoop.h"
#include <sys/epoll.h>

#include <cstdio>

namespace ndsl {
namespace net {

BaseChannel::BaseChannel(int fd, EventLoop *loop)
    : Channel(loop)
    , fd_(fd)
{}

int BaseChannel::getFd() { return fd_; }

int BaseChannel::handleEvent()
{
    if (revents_ & EPOLLIN) {
        if (handleRead_) handleRead_(pThis_);
    }

    if (revents_ & EPOLLOUT) {
        if (handleWrite_) handleWrite_(pThis_);
    }

    return S_OK;
}

int BaseChannel::setCallBack(
    ChannelCallBack handleRead,
    ChannelCallBack handleWrite,
    void *thi)
{
    handleRead_ = handleRead;
    handleWrite_ = handleWrite;
    pThis_ = thi;

    return S_OK;
}

int BaseChannel::enableReading()
{
    events_ |= EPOLLIN;
    return modify();
}

int BaseChannel::enableWriting()
{
    events_ |= EPOLLOUT;
    return modify();
}

int BaseChannel::disableReading()
{
    events_ &= ~EPOLLIN;
    return modify();
}

int BaseChannel::disableWriting()
{
    events_ &= ~EPOLLOUT;
    return modify();
}

int BaseChannel::enroll(bool isET)
{
    if (isET) events_ |= EPOLLET;

    return pLoop_->enroll(this);
}

int BaseChannel::modify() { return pLoop_->modify(this); }

int BaseChannel::erase() { return pLoop_->erase(this); }

} // namespace net
} // namespace ndsl