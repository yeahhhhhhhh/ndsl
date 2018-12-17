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

int BaseChannel::handleEvent()
{
    if (getRevents() & EPOLLIN) { pCb_->handleRead(); }
    if (getRevents() & EPOLLOUT) { pCb_->handleWrite(); }
    return S_OK;
}

int BaseChannel::setCallBack(ChannelCallBack *pCb)
{
    pCb_ = pCb;
    return S_OK;
}

uint32_t BaseChannel::getRevents() { return revents_; }

int BaseChannel::setRevents(uint32_t revents)
{
    revents_ = revents;
    return S_OK;
}

EventLoop *BaseChannel::getEventLoop() { return pLoop_; }

uint32_t BaseChannel::getEvents() { return events_; }

int BaseChannel::enableReading()
{
    events_ |= EPOLLIN;
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

} // namespace net
} // namespace ndsl