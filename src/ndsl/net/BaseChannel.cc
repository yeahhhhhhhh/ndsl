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
    if (getRevents() & EPOLLIN) {
        if (handleRead_) handleRead_(pThis_);
    }

    if (getRevents() & EPOLLOUT) {
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

// int BaseChannel::handleEvent()
// {
//     if (getRevents() & EPOLLIN) { pCb_->handleRead(); }

//     if (getRevents() & EPOLLOUT) { pCb_->handleWrite(); }

//     return S_OK;
// }

// int BaseChannel::setCallBack(ChannelCallBack *cb)
// {
//     pCb_ = cb;
//     return S_OK;
// }

int BaseChannel::enableReading()
{
    setEvents(getEvents() | EPOLLIN);
    update();
    return S_OK;
}

int BaseChannel::enableWriting()
{
    setEvents(getEvents() | EPOLLOUT);
    update();
    return S_OK;
}

int BaseChannel::disableReading()
{
    setEvents(getEvents() & ~EPOLLIN);
    update();
    return S_OK;
}

int BaseChannel::disableWriting()
{
    setEvents(getEvents() & ~EPOLLOUT);
    update();
    return S_OK;
}

int BaseChannel::regist(bool isET)
{
    if (isET) {
        setEvents(getEvents() & EPOLLET);
    } else {
        setEvents(getEvents());
    }
    getEventLoop()->regist(this);
    return S_OK;
}

int BaseChannel::update()
{
    getEventLoop()->update(this);
    return S_OK;
}

int BaseChannel::del()
{
    getEventLoop()->del(this);
    return S_OK;
}

} // namespace net
} // namespace ndsl