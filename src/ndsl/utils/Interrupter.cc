/*
 * @file: Interrupter.cc
 * @brief
 * Interrupter的实现
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <sys/eventfd.h>
#include "ndsl/utils/Interrupter.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace utils {

Interrupter::Interrupter(EventLoop *eloop, int fd)
    : Channel::Channel(eloop, fd)
{}

Interrupter::~Interrupter() {}

// TODO:自定义第一个中断服务函数
int Interrupter::interrupt1()
{
    pLoop_->quit();
    LOG(LEVEL_DEBUG, "Interrupter::interrupt1\n");
}

// TODO:自定义第二个中断服务函数
int Interrupter::interrupt2() { LOG(LEVEL_DEBUG, "Interrupter::interrupt2\n"); }

int Interrupter::handleRead()
{
    int ret = ::eventfd_read(getFd(), &data);
    if (ret < 0) {
        LOG(LEVEL_ERROR, "Interrupter::handleRead eventfd_read\n");
        return S_FAIL;
    }
    if (data == INT1) interrupt1();
    if (data == INT2) interrupt2();
}

} // namespace utils

} // namespace ndsl