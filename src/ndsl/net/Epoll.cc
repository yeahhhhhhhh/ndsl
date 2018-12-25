/**
 * @file Epoll.cc
 * @brief
 * Epoll的实现
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <errno.h>
#include <sys/epoll.h>
#include <string.h>
#include "ndsl/net/Epoll.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/Channel.h"

#include <cstdio>

namespace ndsl {
namespace net {

int Epoll::init()
{
    epfd_ = epoll_create(1);
    if (epfd_ < 0) {
        LOG(LEVEL_ERROR, "Epoll::init epoll_create\n");
        return errno;
    }

    return S_OK;
}

int Epoll::regist(Channel *pCh)
{
    struct epoll_event ev;

    ev.data.ptr = pCh;
    ev.events = pCh->getEvents();

    int ret = ::epoll_ctl(epfd_, EPOLL_CTL_ADD, pCh->getFd(), &ev);

    if (ret < 0) {
        printf(
            "epfd = %d, fd =  %d, ret = %d, errno = %d, strerr = %s\n",
            epfd_,
            pCh->getFd(),
            ret,
            errno,
            strerror(errno));
        LOG(LEVEL_DEBUG, "epoll::control regist\n");
        return errno;
    }

    return S_OK;
}

int Epoll::update(Channel *pCh)
{
    struct epoll_event ev;

    ev.data.ptr = pCh;
    ev.events = pCh->getEvents();

    int ret = ::epoll_ctl(epfd_, EPOLL_CTL_MOD, pCh->getFd(), &ev);

    if (ret < 0) {
        LOG(LEVEL_DEBUG, "epoll::control update\n");
        return errno;
    }

    return S_OK;
}

int Epoll::del(Channel *pCh)
{
    struct epoll_event ev;

    int ret = ::epoll_ctl(epfd_, EPOLL_CTL_DEL, pCh->getFd(), &ev);

    if (ret < 0) {
        LOG(LEVEL_DEBUG, "epoll::control del\n");
        return errno;
    }

    return S_OK;
}

// nEvents返回响应事件数,timeoutMs默认为-1
int Epoll::wait(Channel *channels[], int &nEvents, int timeoutMs)
{
    struct epoll_event events[MAX_EVENTS];
    int ret = ::epoll_wait(epfd_, events, MAX_EVENTS, timeoutMs);

    if (ret < 0) {
        LOG(LEVEL_ERROR, "Epoll::wait epoll_wait\n");
        return errno;
    }

    // 记录响应事件数
    nEvents = ret;

    // 依次读取事件，并返回事件
    for (int i = 0; i < ret; i++) {
        Channel *channel = static_cast<Channel *>(events[i].data.ptr);
        channel->setRevents(events[i].events);
        channels[i] = channel;
    }

    return S_OK;
}

} // namespace net
} // namespace ndsl
