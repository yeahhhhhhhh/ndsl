/*
 * @file TimeWheelTest.cc
 * @brief
 * TimeWheel的单元测试
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "../catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TimeWheel.h"

using namespace ndsl;
using namespace net;

void onTick(void *)
{
    static int ticks = 0;
    printf("Timer onTick: ticks = %d\n", ++ticks);
}

TEST_CASE("net/TimeWheel")
{
    SECTION("start and stop")
    {
        EventLoop eloop;
        REQUIRE(eloop.init() == S_OK);

        TimeWheel tw(&eloop);
        REQUIRE(tw.start() == S_OK);
        REQUIRE(tw.stop() == S_OK);
    }

    SECTION("addTask")
    {
        EventLoop eloop;
        REQUIRE(eloop.init() == S_OK);

        TimeWheel tw(&eloop);
        TimeWheel::Task *task = new TimeWheel::Task;

        task->doit = onTick;
        task->para = NULL;
        task->setInterval = 2;
        task->times = 5;

        tw.addTask(task);
    }
}