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
    : Channel(sockfd, loop)
{}

int TcpChannel::onRead(TcpConnection *pCon, char *inBuf) { pCon->send(inBuf_); }
int TcpChannel::onWrite() {}

int TcpChannel::handleEvent()
{
    if (getRevents() & EPOLLIN) { pCon_->read(); }
    if (getRevents() & EPOLLOUT) { pCon_->write(); }
}

int TcpChannel::setCallBack(TcpConnection *pCon) { pCon_ = pCon; }

} // namespace net
} // namespace ndsl
