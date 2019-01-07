////
// @file PluginTest.cc
// @brief
// 测试Plugin
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include "../catch.hpp"
#include "ndsl/utils/Plugin.h"

using namespace ndsl;
using namespace utils;

int func(int para)
{
    para++;
    return para;
}
TEST_CASE("Plugin")
{
    ndsl::utils::Plugin plugin;
    SECTION("doit")
    {
        REQUIRE(plugin.doit(func,5) == 6);
    }
}