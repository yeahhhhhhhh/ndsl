/**
 * @file Epoll.h
 * @brief
 * 封装epoll
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_EPOLL_H__
#define __NDSL_NET_EPOLL_H__

#include <unistd.h>
#include <sys/epoll.h>
#include <vector>

namespace ndsl {
namespace net {

class Channel;
/*
 * @brief
 * 封装epoll
 */
class Epoll
{
  private:
    int epfd_; // epoll文件描述符

  public:
    static const int MAX_EVENTS = 64; // 设置最大事件响应数

  public:
    Epoll()
        : epfd_(-1)
    {}

    ~Epoll()
    {
        if (epfd_ != -1) ::close(epfd_);
    }

    // 初始化epfd
    int init();

    // 注册、更新、删除事件
    // int regist(Channel *);
    // int update(Channel *);
    // int del(Channel *);

    int enroll(Channel *);
    int modify(Channel *);
    int erase(Channel *);

    // 默认为一直阻塞,nEvents返回响应事件数
    int wait(Channel *channels[], int &nEvents, int timeMs = -1);
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_EPOLL_H__