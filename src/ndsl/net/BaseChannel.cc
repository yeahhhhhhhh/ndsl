/**
 * @file BaseChannel.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/BaseChannel.h"
#include "ndsl/config.h"
#include "ndsl/utils/Log.h"
#include "ndsl/net/EventLoop.h"
#include <sys/epoll.h>

namespace ndsl {
namespace net {

BaseChannel::BaseChannel(int fd, EventLoop *loop)
    : Channel(loop)
    , fd_(fd)
    , pThis_(NULL)
{}

int BaseChannel::getFd() { return fd_; }

int BaseChannel::handleEvent()
{
    // EPOLLHUP EPOLLRDHUP
    // Stream socket peer closed connection, or shut down writing half of
    // connection.  (This flag is especially useful for writing simple code  to
    // detect peer shutdown when using Edge Triggered monitoring.)
    // EPOLLIN | EPOLLRDHUP 对端关闭

    // EPOLLERR 表示相关联的fd发生了错误
    // Error condition happened  on  the  associated  file  descriptor.
    // epoll_wait(2)  will always wait for this event; it is not
    // necessary to set it in events.

    // TODO: 关闭掉fd之后要不要做相应的Channel和Connection的释放 ？
    if ((revents_ & EPOLLIN) && (revents_ & EPOLLHUP)) {
        printf("BaseChannel::handleEvent receive EPOLLHUP\n");
        close(fd_);
    }
    if ((revents_ & EPOLLIN) && (revents_ & EPOLLRDHUP)) {
        printf("BaseChannel::handleEvent receive EPOLLRDHUP\n");
        close(fd_);
    }

    if ((revents_ & EPOLLIN) && (revents_ & EPOLLERR)) {
        printf("BaseChannel::handleEvent receive EPOLLERR\n");
        close(fd_);
    }

    if (revents_ & EPOLLIN) {
        // printf("BaseChannel::handleEvent EPOLLIN\n");
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

int BaseChannel::enrollIn(bool isET)
{
    if (isET) events_ |= EPOLLET;

    events_ |= EPOLLIN;
    return pLoop_->enroll(this);
}

int BaseChannel::erase() { return pLoop_->erase(this); }

} // namespace net
} // namespace ndsl