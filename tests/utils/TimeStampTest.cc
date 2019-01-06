////
// @file TimeStampTest.cc
// @brief
// 测试TimeStamp
//
// @author zhnagsiqi
// @email 1575033031@qq.com
//
#include "../catch.hpp"
#include <string.h>
#include <ndsl/utils/TimeStamp.h>

TEST_CASE("utils/TimeStamp")
{
    SECTION("to_from")
    {
        TimeStamp ts;
        ts.now();
        char buf[512];
        char* time;
        REQUIRE(ts.to_string(buf, 512));
        time = (char*)buf;
        REQUIRE(::strncmp(buf, time, ::strlen(time)) == 0);


        const char *time1 = (const char *)buf;
        ts.from_string(time1);
        REQUIRE(ts.to_string(buf, 512));
        REQUIRE(::strncmp(buf, time1, ::strlen(time1)) == 0);

    }

}