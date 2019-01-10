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
<<<<<<< HEAD
using namespace ndsl;
using namespace utils;
== == == =

>>>>>>> dev_lgr
             == == == =

>>>>>>> dev_zsq

                          int func(int para)
{
    para++;
    return para;
}
TEST_CASE("Plugin")
{
<<<<<<< HEAD
<<<<<<< HEAD
    ndsl::utils::Plugin plugin;
    SECTION("doit")
    {
        // plugin = CreatPlugin();
        REQUIRE(plugin.doit(func, 5) == 6);
        == == == =
                     // ndsl::utils::Plugin plugin;
            SECTION("doit")
        {
            // plugin = CreatPlugin();
            // REQUIRE(plugin.doit(func,5) == 6);
>>>>>>> dev_lgr
            == == == =
                         // ndsl::utils::Plugin plugin;
                SECTION("doit")
            {
                // plugin = CreatPlugin();
                // REQUIRE(plugin.doit(func,5) == 6);
>>>>>>> dev_zsq
            }
        }