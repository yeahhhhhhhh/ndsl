/*
 * @file: Interrupter.h
 * @brief
 * 实现Interrupter,用于EventLoop中断
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_UTILS_INTERRUPTER_H__
#define __NDSL_UTILS_INTERRUPTER_H__

#include <sys/eventfd.h>
#include "ndsl/net/Channel.h"
#include "ndsl/net/EventLoop.h"

namespace ndsl {
namespace utils {

/**
 * @brief
 * Interrupter类，包含一个eventfd，用于线程间通信
 */
class Interrupter : public Channel
{
  private:
    eventfd_t data;
    enum
    {
        INT1 = 1, // 设置第一个中断号
        INT2 = 2  // 设置第二个中断号
    };

  public:
    Interrupter(EventLoop *eloop, int fd);
    ~Interrupter();

  private:
    int handleRead();

    int interrupt1(); //第一个中断服务函数
    int interrupt2(); //第二个中断服务函数
};

} // namespace utils

} // namespace ndsl

#endif // __NDSL_UTILS_INTERRUPTER_H__