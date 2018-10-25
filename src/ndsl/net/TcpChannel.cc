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

#include "../incluce/ndsl/net/TcpChannel.h"

int TcpChannel::onRead(TcpConnection *pCon, char *inBuf) {}
int TcpChannel::onWrite() {}

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

int TcpChannel::getEvents() { return events_; }

int TcpChannel::getFd() { return sockfd_; }

int TcpChannel::update() { pLoop_->update(); }

int TcpChannel::register() { pLoop_->register(); }