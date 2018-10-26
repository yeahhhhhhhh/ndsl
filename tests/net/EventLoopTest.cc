/*
 * @file: EventLoopTest.cc
 * @brief
 * EventLoop的单元测试
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <pthread.h>
#include "catch2/catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/utils/temp_define.h"

using namespace ndsl;
using namespace net;

TEST_CASE("net/EventLoop")
{
    SECTION("quit")
    {
        Epoll ep;
        EventLoop loop(&ep);
        REQUIRE(loop.init() == S_OK);

        pthread_t p_id;
        int ret = ::pthread_create(&p_id, NULL, loop.loop, NULL);

        REQUIRE(loop.quit() == S_OK);

        void *pret;
        ::pthread_join(p_id, &pret);

        REQUIRE((int) pret == S_FAIL);
    }
}