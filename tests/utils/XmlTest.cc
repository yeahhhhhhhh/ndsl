////
// @fiel XmlTest.cc
// @brief
// Xml 测试类
//
// @author zjc
// @email 2324234234@qq.com
//

//#define CATCH_CONFIG_MAIN
#include <fstream>

#include "test.h"
#include "ndsl\include\ndsl\utils\Xml.h"

TEST_CASE("Xml")
{
    std::ifstream stream("phone.xml");
    Xml xml;
    xml_node node(NULL);
    xpath_node_set set;
    std::string str;
    SECTION("xmlparse_test")
    {
        REQUIRE(xml.loadstream(stream) == 0);

        REQUIRE(xml.getfirstnode("phone_books", node) == 0);

        REQUIRE(xml.getnodesets("phone_books", set) == 0);

        //  xml.getfirstnode("Phone_books/phone", node);

        REQUIRE(xml.getpeoperty(node, "id", str) == 0);
        REQUIRE(xml.delproperty(node, "id") == 0);
        REQUIRE(xml.delchidnode(node, "tel") == 0);
        REQUIRE(xml.addChildNode(node, "shit") == 0);
        REQUIRE(xml.setnodetextandattr(node, "friend", "hap", "ship") == 0);
        REQUIRE(xml.savestream(std::cout) == 0);
        // REQUIRE()
    }
}