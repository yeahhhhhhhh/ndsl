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
    if (handleRead)
        handleRead_ = handleRead;
    else
        handleRead_ = NULL;

    if (handleWrite)
        handleWrite_ = handleWrite;
    else
        handleWrite_ = NULL;

    pThis_ = thi;

    return S_OK;
}

int BaseChannel::enableReading()
{
    events_ |= EPOLLIN;
    return update();
}

int BaseChannel::enableWriting()
{
    events_ |= EPOLLOUT;
    return update();
}

int BaseChannel::disableReading()
{
    events_ &= ~EPOLLIN;
    return update();
}

int BaseChannel::disableWriting()
{
    events_ &= ~EPOLLOUT;
    return update();
}

int BaseChannel::regist(bool isET)
{
    if (isET) events_ |= EPOLLET;

    return getEventLoop()->regist(this);
}

int BaseChannel::update() { return getEventLoop()->update(this); }

int BaseChannel::del() { return getEventLoop()->del(this); }

} // namespace net
} // namespace ndsl