/*
 * File: TcpChannel.cc
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Thursday, 29th November 2018 1:30:56 pm
 */

#include "ndsl/net/TcpChannel.h"
#include <sys/epoll.h>

#include <iostream>
using namespace std;

namespace ndsl {
namespace net {

TcpChannel::TcpChannel(int sockfd, EventLoop *loop)
    : sockfd_(sockfd)
    , pLoop_(loop)
{}

// Channel::~Channel() {}

int TcpChannel::onRead(char *inBuf)
{
    // 强制类型转换成实际的类
    // ((TcpConnection *) pCallBack_)->send(inBuf);
    // return S_OK;

    // 测试可以在这动手脚
    char temp[MAXLINE] = "received";
    ((TcpConnection *) pCallBack_)->send(temp);
    return S_OK;
}

int TcpChannel::onWrite() { return S_OK; }

int TcpChannel::handleEvent()
{
    cout << "TcpChannel::handleEvent" << endl;

    if (getRevents() & EPOLLIN) { pCallBack_->handleRead(); }
    if (getRevents() & EPOLLOUT) { pCallBack_->handleWrite(); }
    return S_OK;
}

int TcpChannel::setCallBack(ChannelCallBack *pCB)
{
    pCallBack_ = pCB;
    return S_OK;
}

uint64_t TcpChannel::getRevents() { return revents_; }

int TcpChannel::setRevents(uint64_t revents)
{
    revents_ = revents;
    return S_OK;
}

EventLoop *TcpChannel::getEventLoop() { return pLoop_; }

uint64_t TcpChannel::getEvents() { return events_; }

int TcpChannel::enableReading()
{
    events_ |= EPOLLIN;
    regist();
    return S_OK;
}

int TcpChannel::enableWriting()
{
    events_ |= EPOLLOUT;
    update();
    return S_OK;
}

int TcpChannel::disableWriting()
{
    events_ &= ~EPOLLOUT;
    update();
    return S_OK;
}

int TcpChannel::isWriting() { return events_ & EPOLLOUT; }

int TcpChannel::update()
{
    getEventLoop()->update(this);
    return S_OK;
}

int TcpChannel::regist()
{
    cout << "TcpChannel::regist" << endl;

    getEventLoop()->regist(this);
    return S_OK;
}

int TcpChannel::del()
{
    getEventLoop()->del(this);
    return S_OK;
}

int TcpChannel::getFd() { return sockfd_; }

} // namespace net
} // namespace ndsl
