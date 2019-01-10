////
// @file GuidTest.cc
// @brief
<<<<<<< HEAD
<<<<<<< HEAD
// Guid测试类
== == == =
             // Guid测试
>>>>>>> dev_lgr
    == == == =
// Guid测试
>>>>>>> dev_zsq
//
// @author why
// @email 136046355@qq.com
//
<<<<<<< HEAD
<<<<<<< HEAD
//#define CATCH_CONFIG_MAIN
#        include "../catch.hpp"
#        include "ndsl/utils/Guid.h"
#        include <iostream>
                 == == == =
#        include "../catch.hpp"
#        include "ndsl/utils/Guid.h"
>>>>>>> dev_lgr
                              == == == =
#    include "../catch.hpp"
#    include "ndsl/utils/Guid.h"
>>>>>>> dev_zsq

                                           TEST_CASE("Guid")
{
    ndsl::utils::Guid g1, g2;

    SECTION("generate") { REQUIRE(g1.generate() == 0); }
    SECTION("toString")
    {
        char str[32];
        g1.generate();
        g1.toString(str);
<<<<<<< HEAD
<<<<<<< HEAD
        std::cout << str << std::endl;
        == == == =
                     //		std::cout << str << std::endl;
>>>>>>> dev_lgr
            == == == =
                         //		std::cout << str << std::endl;
>>>>>>> dev_zsq
            REQUIRE(g1.toString(str) == 0);
    }
    SECTION("toGuid_t")
    {
        char str[33] = "0D1A1E81BA3540B493340D84B61775E2";
        g1.toGuid_t(str);
        REQUIRE(g1.toGuid_t(str) == 0);
    }
    SECTION("operator==")
    {
        char str[33] = "0D1A1E81BA3540B493340D84B61775E2";
        g1.toGuid_t(str);
        char str2[33] = "0D1A1E81BA3540B493340D84B61775E2";
        g2.toGuid_t(str2);
        REQUIRE((g1 == g2) == true);
    }
    SECTION("operator<")
    {
        char str[33] = "0D1A1E81BA3540B493340D84B61775E2";
        g1.toGuid_t(str);
        char str2[33] = "A000277BA39B4384AFC4A05CE8CFA6DD";
        g2.toGuid_t(str2);
        REQUIRE((g1 < g2) == true);
    }
    SECTION("operator>")
    {
        char str[33] = "0D1A1E81BA3540B493340D84B61775E2";
        g1.toGuid_t(str);
        char str2[33] = "A000277BA39B4384AFC4A05CE8CFA6DD";
        g2.toGuid_t(str2);
        REQUIRE((g2 > g1) == true);
    }
}
