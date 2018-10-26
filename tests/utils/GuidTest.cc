////
// @file GuidTest.cc
// @brief
// Guid测试类
//
// @author why
// @email 136046355@qq.com
//
#include "../../include/ndsl/utils/Guid.h"

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"


TEST_CASE("Guid"){
	ndsl::utils::Guid g;
	guid_t gu1, gu2;
	char str1[32], str2[32];
	SECTION("stringGenerate"){
		char str[32];
		g.guidStringGenerate(str);
		std::cout << str << std::endl;
	}
	SECTION("guidGenerate"){
		g.guidGenerate(gu1);
		g.guidGenerate(gu2);
	}
	SECTION("guidCompare"){
		int ret = g.guidCompare(gu1, gu2);
		std::cout << ret << std::endl;
	}
	SECTION("guid2String"){	
		g.guid2String(gu1, str1);
		g.guid2String(gu2, str2);
		std::cout << str1 << std::endl;
		std::cout << str2 << std::endl;
	}
	SECTION("guidStringCompare"){
		int ret = g.guidStringCompare(str1, str2);
		std::cout << ret << std::endl;
	}
}