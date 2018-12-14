/**
 * @file TimeWheel.cc
 * @brief
 *
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "ndsl/net/TimeWheel.h"

namespace ndsl {
namespace net {
TimerfdChannel::TimerfdChannel(int fd, EventLoop *loop) {}

TimerfdChannel::~TimerfdChannel() {}

TimerWheel::TimerWheel(EventLoop *loop, long intervalMs, int slotNum)
    : pLoop_(loop)
    , ptimerfdChannel_(NULL)
    , intervalMs_(intervalMs)
    , slotNum_(slotNum)
    , tick_(1)
{}

TimerWheel::~TimerWheel()
{
    if (ptimerfdChannel_) delete ptimerfdChannel_;
}

// 初始化,创建TimerfdChannel
int TimerWheel::init()
{
    int fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if (fd == -1) {
        LOG(LEVEL_ERROR, "TimerWheel::init timerfd_create error!\n");
        return errno;
    }

    ptimerfdChannel_ = new TimerfdChannel(fd, pLoop_);

    return S_OK;
}

int TimerWheel::start()
{
    int ret = init();
    if (ret != S_OK) { return ret; }

    // 设置时间轮的时间间隔
    struct itimerspec new_value;
    struct timespec now;

    if (clock_gettime(CLOCK_MONOTONIC, &now) == -1) {
        LOG(LEVEL_ERROR, "TimerWheel::init clock_gettime error!\n");
        return errno;
    }

    new_value.it_value.tv_sec = now.tv_sec;
    new_value.it_value.tv_nsec = now.tv_nsec;

    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_nsec = intervalMs_ * 1000000; // 把单位转换为纳秒

    if (timerfd_settime(ptimerfdChannel_->getFd(), 0, &new_value, NULL) == -1) {
        LOG(LEVEL_ERROR, "TimerWheel::init timerfd_settime error!\n");
        return errno;
    }

    ptimerfdChannel_->enableReading();

    return S_OK;
}

// 停止时间轮
int TimerWheel::stop()
{
    if (timerfd_settime(ptimerfdChannel_->getFd(), 0, 0, NULL) == -1) {
        LOG(LEVEL_ERROR, "TimerWheel::init timerfd_settime error!\n");
        return errno;
    }

    return S_OK;
}

} // namespace net
} // namespace ndsl