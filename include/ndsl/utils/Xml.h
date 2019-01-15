////
// @file Xml.h
// @brief
// 解析xml文件,主要用于配置文件的读取
//
// @author zhujicheng
// @email 2364464666@qq.com
//

#ifndef __NDSL_UTILS_XML_H__
#define __NDSL_UTILS_XML_H__

#include <string>
#include <iostream>
//#include <fstream>
#include "ndsl/include/ndsl/third/pugixml.hpp"
//#include "ndsl/thirdlib/pugiconfig.hpp"
#include "Error.h"

using namespace pugi;

class XML
{
  public:
    XML();

    ~XML();

    //从流中导入文件
    int loadstream(std::istream &stream);
    //保存到流中
    int savestream(std::ostream &stream);

    //获取满足xpath条件的第一个节点
    int getfirstnode(const char *xpath, xml_node &node);
    //获取xpath查询条件的所有节点
    int getnodesets(const char *xpath, xpath_node_set &sets);
    //获取，设置，删除节点属性信息
    int getproperty(xml_node node, const char *property, std::string &value);

    int delproperty(xml_node &node, const char *property);

    int setnodetextandattr(
        xml_node &node,
        const char *text,
        const char *attr,
        const char *value);
    int delchildnode(xml_node &node, const char *child);
    int addchildnode(xml_node &parentnode, const char *nodename);
    // int addnode(xml_node);

  private:
    xml_document m_doc;
    xml_node m_node;
};
#endif