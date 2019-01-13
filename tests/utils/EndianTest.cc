////
// @file EndianTest.cc
// @brief
// 测试Endian
//
// @author lanyue
// @email luckylanry@163.com 
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "ndsl/utils/Endian.h"


TEST_CASE("utils/Endian")
{   
    ndsl::utils::Endian e;

    // SECTION("hToN64"){
    //      uint64_t ret=e.hToN64(u64t);
    //      std::cout << ret << std::endl;
    // }
    //  SECTION("hToN32"){
    //    int32_t ret= e.hToN32(65);
    //    std::cout << ret << std::endl;
    // }
     SECTION("hToN16"){
        uint16_t u16t = 13;
        e.hToN16(u16t);
    //    std::cout << ret << std::endl;
    }

    // SECTION("nToH64"){
    //    uint64_t ret= e.nToH64(67);
    //    std::cout << ret << std::endl;
    // }
    //  SECTION("nToH32"){
    //    uint32_t ret= e.nToH32(68);
    //    std::cout << ret << std::endl;
    // }
    //  SECTION("nToH16"){
    //    uint16_t ret= e.hToN16(69);
    //    std::cout << ret << std::endl;
    // }
    

}  