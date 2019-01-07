////
// @file TimeStampTest.cc
// @brief
// 测试TimeStamp
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include "../catch.hpp"
#include <string.h>
#include <ndsl/utils/Log.h>

TEST_CASE("utils/Log")
{
    SECTION("LOG")
    {
        
        LOG(LOG_ERROR_LEVEL, 0,"hello, world\n");
        LOG(LOG_DEBUG_LEVEL,1,"DEBUG\n");

        
    }
}
