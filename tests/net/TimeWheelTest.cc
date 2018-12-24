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

void func3(void *para)
{
    printf("Call func2 and para is %s!\n", (char *) para);
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

    // 如何测?
    // SECTION("addTask")
    // {
    //     EventLoop eloop;
    //     REQUIRE(eloop.init() == S_OK);

    //     TimeWheel tw(&eloop);
    //     TimeWheel::Task *task = new TimeWheel::Task;

    //     task->doit = func2;
    //     task->para = (void *) "Hello World";
    //     task->setInterval = 2;
    //     task->times = 5;

    //     tw.addTask(task);

    //     eloop.loop();
    // }
}