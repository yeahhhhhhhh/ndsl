/*
 * @file: Interrupter.cc
 * @brief
 * Interrupter的实现
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <errno.h>
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

int Interrupter::getFd() { return Channel::getFd(); }

int Interrupter::interrupt()
{
    data = 1;
    while (1) {
        int ret = eventfd_write(getFd(), data);

        if (ret < 0) {
            if (errno == EWOULDBLOCK) continue;

            LOG(LEVEL_ERROR, "Interrupter::interrupt eventfd_write\n");
            return errno;
        } else
            break;
    }
    return S_OK;
}

// TODO:自定义第一个中断服务函数
int Interrupter::interrupt1()
{
    Channel::getEventLoop()->quit();
    LOG(LEVEL_DEBUG, "Interrupter::interrupt1\n");
}

// TODO:自定义第二个中断服务函数
int Interrupter::interrupt2() { LOG(LEVEL_DEBUG, "Interrupter::interrupt2\n"); }

int Interrupter::handleRead()
{
    data = 0;
    int ret = ::eventfd_read(Channel::getFd(), &data);
    if (ret < 0) {
        LOG(LEVEL_ERROR, "Interrupter::handleRead eventfd_read\n");
        return S_FAIL;
    }
    if (data == INT1) interrupt1();
    if (data == INT2) interrupt2();
}

} // namespace utils

} // namespace ndsl