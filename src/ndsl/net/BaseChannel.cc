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
    // TODO: EPOLL HUG 四个

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

int BaseChannel::enroll(bool isET)
{
    if (isET) events_ |= EPOLLET;

    // 同时注册输入输出
    events_ |= EPOLLIN;
    events_ |= EPOLLOUT;

    return pLoop_->enroll(this);
}

int BaseChannel::erase() { return pLoop_->erase(this); }

} // namespace net
} // namespace ndsl