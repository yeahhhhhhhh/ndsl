/*
 * @file CallbackIoChannel.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "CallbackIoChannel.h"

namespace nadl {
namespace net {

CallbackIoChannel::CallbackIoChannel(
    int sockFd,
    void *buf, // FIXME: void * --> char *
    size_t &len,
    int flag,
    Callback cb,
    void *param,
    EventLoop *loop)
    : sockFd_(sockFd)
    , buf_(buf)
    , len_(len)
    , flag_(flag)
    , cb_(cb)
    , param_(param)
    , loop_(loop)

{}

int CallbackIoChannel::enableReading()
{
    events_ |= EPOLLIN;
    regist();
    return S_OK;
}

int CallbackIoChannel::enableWriting()
{
    events_ |= EPOLLOUT;
    update();
    return S_OK;
}

int CallbackIoChannel::disableWriting()
{
    events_ &= ~EPOLLOUT;
    update();
    return S_OK;
}

int CallbackIoChannel::update()
{
    getEventLoop()->update(this);
    return S_OK;
}

int CallbackIoChannel::getEventLoop() { return pLoop_; }

uint32_t CallbackIoChannel::getRevents() { return revents_; }

int CallbackIoChannel::handleEvent()
{
    if (getRevents() & EPOLLIN) { handleRead(); }
    if (getRevents() & EPOLLOUT) { handleWrite(); }
    cb_(param_);
    return S_OK;
}

int CallbackIoChannel::getFd() { return sockFd_; }

int CallbackIoChannel::regist()
{
    pLoop_->regist(this);
    return S_OK;
}

int CallbackIoChannel::handleRead()
{
    memset(buf_, 0, sizeof(buf_));

    if ((len_ = read(sockFd_, buf_, MAXLINE)) < 0) {
        if (errno == ECONNRESET) { close(sockFd_); }
    } else if (len_ == 0) {
        close(sockFd_);
    }

    return S_OK;
}

int CallbackIoChannel::handleWrite()
{
    // FIXME: 如果系统buffer不够，则需要回调，在回调之前，无法使用bufferz
    write(sockFd_, buf_, len_);
    return S_OK;
}

} // namespace net
} // namespace nadl