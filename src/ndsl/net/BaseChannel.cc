/**
 * @file BaseChannel.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/BaseChannel.h"
#include <sys/epoll.h>

namespace ndsl {
namespace net {

BaseChannel::BaseChannel(int fd, EventLoop *loop)
    : fd_(fd)
    , Channel(loop)
{}

int BaseChannel::handleEvent()
{
    if (getRevents() & EPOLLIN) { pCb_->handleRead(); }
    if (getRevents() & EPOLLOUT) { pCb_->handleWrite(); }
    return S_OK;
}

int BaseChannel::getFd() { return fd_; }

int BaseChannel::setCallBack(ChannelCallBack *pCb)
{
    pCb_ = pCb;
    return S_OK;
}

int BaseChannel::enableReading()
{
    setEvents(getEvents() | EPOLLIN);
    update();
    return S_OK;
}

int BaseChannel::enableWriting()
{
    events_ |= EPOLLOUT;
    update();
    return S_OK;
}

int BaseChannel::disableReading()
{
    events_ &= ~EPOLLIN;
    update();
    return S_OK;
}

int BaseChannel::disableWriting()
{
    events_ &= ~EPOLLOUT;
    update();
    return S_OK;
}

int BaseChannel::regist()
{
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

int BaseChannel::changeMode2ET()
{
    getEventLoop()->changeMode2ET();
    return S_OK;
}

int BaseChannel::changeMode2LT()
{
    getEventLoop()->changeMode2LT();
    return S_OK;
}

} // namespace net
} // namespace ndsl