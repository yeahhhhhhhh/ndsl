
#include "ndsl/utils/Xml.h"

namespace ndsl {
namespace utils {
XML::XML()
    : m_doc()
    , m_node(NULL)
{}

XML::~XML() {}

int XML::loadstream(std::istream &stream)
{
    if (m_doc.load(stream))
        return S_OK;
    else
        return S_FALSE;
}

int XML::getproperty(xml_node node, const char *property, std::string &value)
{
    value = node.child(property).text().get();
    return S_OK;
}

int XML::delproperty(xml_node &node, const char *property)
{
    if (node.remove_attribute(property))
        return S_OK;
    else
        return S_FALSE;
}

int XML::delchildnode(xml_node &node, const char *child)
{
    if (node.remove_child(child))
        return S_OK;
    else
        return S_FALSE;
}

int XML::getnodesets(const char *xpath, xpath_node_set &sets)
{
    /* xpath_query query_remote_tool(xpath);
     if (sets = query_remote_tool.evaluate_node_set(m_doc))
         return S_OK;
     else
         return S_FALSE;
         */
    xpath_query query_remote_tool(xpath);
    sets = query_remote_tool.evaluate_node_set(m_doc);
    return S_OK;
}

int XML::getfirstnode(const char *xpath, xml_node &node)
{
    node = m_doc.first_element_by_path(xpath);
    return S_OK;
}

int XML::addchildnode(xml_node &parentnode, const char *nodename)
{
    if (parentnode.append_child(nodename)) {
        return S_OK;
    } else
        return S_FALSE;
}

int XML::setnodetextandattr(
    xml_node &node,
    const char *text,
    const char *attr,
    const char *value)
{
    node.text().set(text);
    node.append_attribute(attr).set_value(value);
    return S_OK;
}

int XML::savestream(std::ostream &stream)
{
    m_doc.save(stream);
    return S_OK;
}
} // namespace utils
} // namespace ndsl