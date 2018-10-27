/*
 * File: TcpChannel.cc
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Saturday, 20th October 2018 3:46:31 pm
 * -----
 * Copyright 2018 - 2018
 */

#include "ndsl/net/TcpChannel.h"
#include <sys/epoll.h>

namespace ndsl {
namespace net {

TcpChannel::TcpChannel(int sockfd, EventLoop *loop)
    : sockfd_(sockfd)
    , pLoop_(loop)
{}

int TcpChannel::onRead(TcpConnection *pCon, char *inBuf) { pCon->send(inBuf_); }
int TcpChannel::onWrite() {}

int TcpChannel::handleEvent()
{
    if (getRevents() & EPOLLIN) { pCon_->read(); }
    if (getRevents() & EPOLLOUT) { pCon_->write(); }
}

int TcpChannel::setCallBack(TcpConnection *pCon) { pCon_ = pCon; }

int TcpChannel::getRevents() { return revents_; }

EventLoop *TcpChannel::getEventLoop() { return pLoop_; }

int TcpChannel::getEvents() { return events_; }

int TcpChannel::enableReading()
{
    events_ |= EPOLLIN;
    register();
}

int TcpChannel::enableWriting()
{
    events_ |= EPOLLOUT;
    update();
}

int TcpChannel::disableWriting()
{
    events_ &= ~EPOLLOUT;
    update();
}

int TcpChannel::isWriting() { return events_ & EPOLLOUT; }

int TcpChannel::update() { getEventLoop()->update(this); }

int TcpChannel::regist() { getEventLoop()->register(this); }

int TcpChannel::del() {}

int TcpChannel::getFd() { return fd_; }

} // namespace net
} // namespace ndsl
