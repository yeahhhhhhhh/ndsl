////
// @file PluginTest.cc
// @brief
// 测试Plugin
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include "../catch.hpp"
#include "ndsl/config.h"
#include "ndsl/utils/Plugin.h"

<<<<<<< HEAD


void func(void* para)
=======
int func(int para)
>>>>>>> master
{
    printf("func!\n");
}

TEST_CASE("Plugin")
{
<<<<<<< HEAD
    SECTION("doit")
    {      
        Plugin1* plugin;
        plugin = (Plugin1 *)CreatPlugin(1);
        REQUIRE(plugin->doit(func,NULL) == S_OK);
=======
    // ndsl::utils::Plugin plugin;
    SECTION("doit")
    {
        // plugin = CreatPlugin();
        // REQUIRE(plugin.doit(func,5) == 6);
>>>>>>> master
    }
}