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
        set_ndsl_log_sinks(LOG_SOURCE_EPOLL | LOG_SOURCE_EVENTLOOP | LOG_SOURCE_EVENTLOOPTHREADPOOL ,LOG_OUTPUT_FILE);
=======
        set_ndsl_log_sinks(
            LOG_SOURCE_EPOLL | LOG_SOURCE_EVENTLOOP, LOG_OUTPUT_FILE);
>>>>>>> master_1
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_EVENTLOOP, "hello, world\n");
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_EPOLL, "debug\n");
        LOG(LOG_ERROR_LEVEL,LOG_SOURCE_EVENTLOOPTHREADPOOL,"EventLoopThreadpool::getNextEventLoop");
    }
    SECTION("LOG1")
    {
        uint64_t LOG_SOURCE_MODULE = add_source();
        set_ndsl_log_sinks(LOG_SOURCE_MODULE,LOG_OUTPUT_FILE);
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_MODULE, "hello, world\n");
               
    }
}
