/*
 * @file: InterruptChannel.cc
 * @brief
 * 实现中断eventloop的channel
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include "ndsl/net/InterruptChannel.h"
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace net {
InterruptChannel::InterruptChannel(int fd, EventLoop *loop)
    : Channel(fd, loop)
{}

int InterruptChannel::onRead() {}

int InterruptChannel::onWrite()
{
    uint64_t data = 1;
    int ret = write(this->getFd(), &data, sizeof(data));

    if (ret != sizeof(data)) LOG(LEVEL_ERROR, "EventLoop::interrupter write");
}

int InterruptChannel::handleEvent() {}

} // namespace net
} // namespace ndsl