
#include "ndsl/include/utils/Xml.h"

Xml::Xml()
    : m_doc()
    , m_node(NULL);
{}

Xml::~Xml() {}

int Xml::lodestream(ifstream &stream)
{
    if (m_doc.load(stream))
        return S_OK;
    else
        return s_FAIL;
}

int Xml::getproperty(xml_node node, const char *property, std::string &value)
{
    if (value = node.child(property).text().get())
        return S_OK;
    else
        return S_FALSE;
}

int Xml::delproperty(xml_node &node, const char *property)
{
    if (node.remove_attribute(property))
        return S_OK;
    else
        return S_FALSE;
}

int Xml::delchildnode(xml_node &node, const char *child)
{
    if (node.remove_child(child))
        return S_OK;
    else
        return S_FALSE;
}

int Xml::getnodesets(const char *xpath, xpath_node_set &sets)
{
    xpath_query query_remote_tool(xpath);
    if (sets = query_remote_tool.evaluate_node_set(m_doc))
        return S_OK;
    else
        return S_FALSE;
}

int Xml::getfirstnode(const char *xpath, xml_node &node)
{
    if (node = m_doc.first_element_by_path(xpath))
        return S_OK;
    else
        return S_FALSE;
}

int Xml::addchildnode(xml_node &parentnode, const char *nodename)
{
    if (parentnode.append_child(nodename)) {
        return S_OK;
    } else
        return S_FLASE;
}

int Xml::setnodetextandattr(
    xml_node &node,
    const char *text,
    const char *attr,
    const char *value)
{
    node.text().set(text);
    node.append_attribute(attr).set_value(value);
    return S_OK;
}

int savestream(std::ofstream &stream)
{
    if (m_doc.save(stream))
        return S_OK;
    else
        return S_FALSE;
}
