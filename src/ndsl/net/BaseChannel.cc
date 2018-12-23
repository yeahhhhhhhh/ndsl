/**
 * @file BaseChannel.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/BaseChannel.h"
#include "ndsl/utils/temp_define.h"
#include <sys/epoll.h>

namespace ndsl {
namespace net {

BaseChannel::BaseChannel(int fd, EventLoop *loop)
    : fd_(fd)
    , Channel(loop)
{}

int BaseChannel::handleEvent()
{
    if (getRevents() & EPOLLIN) {
        if (handleRead_) handleRead_();
    }

    if (getRevents() & EPOLLOUT) {
        if (handleWrite_) handleWrite_();
    }

    return S_OK;
}

int BaseChannel::getFd() { return fd_; }

int BaseChannel::setCallBack(
    ChannelCallBack handleRead,
    ChannelCallBack handleWrite);
{
    if (handleRead)
        handleRead_ = handleRead;
    else
        handleRead_ = NULL;

    if (handleWrite)
        handleWrite_ = handleWrite;
    else
        handleWrite_ = NULL;

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
        setEvents(getEvents() & ~EPOLLET);
    } else {
        setEvents(getEvents() & ~EPOLLLT);
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