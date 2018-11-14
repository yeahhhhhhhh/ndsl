/*
 * @file: InterruptChannel.cc
 * @brief
 * 实现中断eventloop的channel
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <unistd.h>
#include "ndsl/net/InterruptChannel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace net {
InterruptChannel::InterruptChannel(int fd, EventLoop *loop)
    : Channel(fd, loop)
{}

InterruptChannel::~InterruptChannel()
{
    if (getFd() >= 0) { ::close(getFd()); }
}

// 没有重载
int InterruptChannel::onRead() { return S_OK; }

// 发送中断信号
int InterruptChannel::onWrite()
{
    uint64_t data = 1;
    int ret = write(this->getFd(), &data, sizeof(data));

    if (ret != sizeof(data)) {
        LOG(LEVEL_ERROR, "EventLoop::interrupter write");
        return errno;
    }

    return S_OK;
}

// 没有重载
int InterruptChannel::handleEvent() { return S_OK; }

} // namespace net
} // namespace ndsl