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
<<<<<<< HEAD
        set_ndsl_log_level(LOG_ERROR_LEVEL);
        LOG(LOG_ERROR_LEVEL, "./test.log","hello, world\n");
        set_ndsl_log_level(LOG_DEBUG_LEVEL);
=======
        
        LOG(LOG_ERROR_LEVEL, 0,"hello, world\n");
        LOG(LOG_DEBUG_LEVEL,1,"DEBUG\n");

        
>>>>>>> dev_lgr
    }
}
