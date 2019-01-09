/**
 * @file ThreadTest.cc
 * @brief
 * 线程和线程池的单元测试
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "../catch.hpp"
#include "ndsl/utils/Thread.h"
#include "ndsl/utils/Error.h"

using namespace ndsl;
using namespace utils;

void *test1(void *arg)
{
    printf("This is thread %ld\n", (long) arg);
    return (void *) 0;
}

TEST_CASE("Thread")
{
    SECTION("run and join")
    {
        Thread t1(test1, (void *) 1);
        REQUIRE(t1.run() == S_OK);

        REQUIRE(t1.join() == S_OK);
    }
}

TEST_CASE("Threadpool")
{
    Threadpool thpool;

    SECTION("create and join")
    {
        int ret = thpool.create(test1, (void *) 2);
        REQUIRE(ret == S_OK);

        ret = thpool.create(test1, (void *) 3);
        REQUIRE(ret == S_OK);

        ret = thpool.join();
        REQUIRE(ret == S_OK);
    }

    SECTION("size")
    {
        int ret = thpool.create(test1, (void *) 4);
        REQUIRE(ret == S_OK);

        ret = thpool.create(test1, (void *) 5);
        REQUIRE(ret == S_OK);

        ret = thpool.size();
        REQUIRE(ret == 2);

        ret = thpool.join();
        REQUIRE(ret == S_OK);
    }
}