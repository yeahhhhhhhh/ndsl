/*
 * @file: InterruptChannel.cc
 * @brief
 * 实现中断eventloop的channel
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <unistd.h>
#include <errno.h>
#include "ndsl/net/InterruptChannel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/WorkQueue.h"

namespace ndsl {
namespace net {
InterruptChannel::InterruptChannel(int fd, EventLoop *loop)
    : Channel(fd, loop)
{}

InterruptChannel::~InterruptChannel()
{
    if (getFd() >= 0) { ::close(getFd()); }
}

// 添加任务
int InterruptChannel::addWork(work_struct *work) { workqueue_->enQueue(work); }

// 没有重载
int InterruptChannel::onRead()
{
    uint64_t recvData;
    int ret = ::read(this->getFd(), &recvData, sizeof(recvData));

    if (ret == -1) {
        // TODO:
        // 做判断,若没有读到,则返回
        if (errno == EINTR ||) }
    return S_OK;
}

// 发送中断信号
int InterruptChannel::onWrite()
{
    uint64_t data = 1;
    int ret = ::write(this->getFd(), &data, sizeof(data));

    if (ret == -1) {
        LOG(LEVEL_ERROR, "EventLoop::interrupter write");
        return errno;
    }

    return S_OK;
}

// 处理队列中的任务
int InterruptChannel::handleEvent()
{
    // TODO:read

    while (!workqueue_->empty()) {
        workqueue_->doit();
    }
    return S_OK;
}

} // namespace net
} // namespace ndsl