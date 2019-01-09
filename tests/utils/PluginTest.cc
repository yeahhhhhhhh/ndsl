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



int func(int para)
{
    para++;
    return para;
}
TEST_CASE("Plugin")
{
    //ndsl::utils::Plugin plugin;
    SECTION("doit")
    {    
        //plugin = CreatPlugin();
        //REQUIRE(plugin.doit(func,5) == 6);
    }
}