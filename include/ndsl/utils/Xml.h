////
// @file Xml.h
// @brief
// xml的解析库的封装，主要用于读取配置文件
//
// @author zjc
// @email zjc@email.com
//
#ifndef __NDSL_UTILS_XML_H__
#define __NDSL_UTILS_XML_H__
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xmlreader.h>
#include <string>
#include <vector>

namespace ndsl {

namespace utils {

class Xml
{
  public:
    Xml();
    ~Xml();
    // 从内存中导入xml数据
    xmlNode *loadmemory(const char *xbuf, unsigned int size);
    //
    xmlNode *createxmlbuffer(const char *rootname);
    // 查找第一个满足xpath条件的节点
    int getfirstnode(const char *xpath, xmlNode *&node);
    // 查询满足条件的所有的节点
    int getnodeset(const char *xpath, std::vector<xmlNode *> &nodes);

    //  获取子节点
    int
    getchildren(const xmlNode *curnode, std::vector<xmlNode *> &children) const;
    // 从当前节点中获取某个子节点
    // int getspecialchild(const xmlNode *curnode, const char *nodename) const;
    // 从当前节点获取子节点集
    int getspecialchildren(
        const xmlNode *curnode,
        const char *nodename,
        std::vector<xmlNode *> &nodes) const;

    // 获取节点属性
    int
    getproperty(const xmlNode *node, const char *property, std::string &value);
    // 设置节点属性
    int setproperty(xmlNode *node, const char *property, const char *value);
    // 删除属性
    int delproperty(xmlNode *node, const char *property);
    //增加子节点
    xmlNode *
    addsimplechild(xmlNode *parent, const char *nodename, const char *value);
    xmlNode *addchild(xmlNode *parent, xmlNode *cur);

    int getfirstnodevalue(const char *xpath, std::string &value);

    xmlNode *getrootnode();

  private:
    xmlDocPtr m_pdoc;          // doc
    xmlNodePtr m_proot;        // 根节点
    xmlBufferPtr m_pbuf;       // buffer
    xmlTextReaderPtr m_reader; //
    std::vector<xmlchar *> m_attrs;
}；
} // namespace utils
} // namespace ndsl

#endif //__NDSL_UTILS_XML_H__
