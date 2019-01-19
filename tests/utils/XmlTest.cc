////
// @fiel XmlTest.cc
// @brief
// Xml 测试类
//
// @author zjc
// @email 2324234234@qq.com
//
#include "../catch.hpp"
#include "ndsl/utils/Xml.h"
#include <fstream>

TEST_CASE("Xml")
{
    std::ifstream stream1("../tests/utils/phone.xml");

    ndsl::utils::XML xml;
    xml_node node(NULL);
    xpath_node_set set;
    std::string str;
    xml.loadstream(stream1);
    SECTION("xmlparse_test")
    {
        REQUIRE(xml.getfirstnode("phone_books/phone", node) == 0);

        REQUIRE(xml.getproperty(node, "id", str) == 0);
        REQUIRE(xml.delproperty(node, "id") == 0);
        REQUIRE(xml.delchildnode(node, "tel") == 0);
        REQUIRE(xml.addchildnode(node, "shit") == 0);
        REQUIRE(xml.setnodetextandattr(node, "friend", "hap", "ship") == 0);
        REQUIRE(xml.savestream(std::cout) == 0);
    }
}