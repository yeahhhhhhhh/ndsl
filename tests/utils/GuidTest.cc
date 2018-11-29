////
// @file GuidTest.cc
// @brief
// Guid测试类
//
// @author why
// @email 136046355@qq.com
//
#include "Guid.h"

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"


TEST_CASE("Guid"){
	ndsl::utils::Guid g, g1;
	guid_t gu1, gu2;
	char str1[32], str2[32];
		
	SECTION("generate"){
		g.generate(gu1);
		g1.generate(gu2);
	}
	SECTION("toString"){	
		g.toString(gu1, str1);
		g1.toString(gu2, str2);
		std::cout << str1 << std::endl;
		std::cout << str2 << std::endl;
	}
	SECTION("pack"){
		g.pack(g, gu1);
	}
	SECTION("unpack"){
		g.unpack(gu1, g);
	}
	SECTION("operator=="){
		bool b = g == g2;
		std::cout << b << std::endl;
	}
}
