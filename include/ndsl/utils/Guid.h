////
// @file Guid.h
// @brief
// Guid工具类
//
// @author why
// @email 136046355@qq.com
//
#ifndef __GUID_H__
#define __GUID_H__

namespace ndsl {
namespace utils {

typedef unsigned char guid_t[16];
class Guid{
    public:
    	Guid();
    
    public:
      void guidGenerate(guid_t gu); // 生成guid
      void guid2String(guid_t gu, char* str); // 将guid转换成字符串
      int guidCompare(guid_t gu1, guid_t gu2); // 比较两个guid，相同则返回0
      void guidStringGenerate(char* str); // 直接生成字符串类型的guid
      int guidStringCompare(char* str1, char* str2); // 比较字符串类型的guid
}; 

} // namespace utils
} // namespace ndsl
#endif // __GUID_H__