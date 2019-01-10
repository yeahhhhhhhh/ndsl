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

<<<<<<< HEAD
using namespace ndsl;
using namespace utils;
=======

>>>>>>> dev_lgr

int func(int para)
{
    para++;
    return para;
}
TEST_CASE("Plugin")
{
<<<<<<< HEAD
    ndsl::utils::Plugin plugin;
    SECTION("doit")
    {    
        //plugin = CreatPlugin();
        REQUIRE(plugin.doit(func,5) == 6);
=======
    //ndsl::utils::Plugin plugin;
    SECTION("doit")
    {    
        //plugin = CreatPlugin();
        //REQUIRE(plugin.doit(func,5) == 6);
>>>>>>> dev_lgr
    }
}