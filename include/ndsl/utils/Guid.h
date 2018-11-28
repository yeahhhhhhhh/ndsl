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

#include<stdint.h>

#define COMPARE(gu1, gu2) if(gu1 != gu2) return false

typedef unsigned char guid_t[16];

namespace ndsl {
namespace utils {

class Guid{
    public:
      Guid();
      
    private:
      uint32_t time_low;
	  uint16_t time_mid;
	  uint16_t time_hi_and_version;
	  uint16_t clock_seq;
	  uint8_t node[6];
    
    public:
      void generate(guid_t gu); // 生成guid，返回guid_t，并解包
      void toString(guid_t gu, char* str); // 将guid_t转换成字符串
      void pack(const Guid &guid, guid_t &out); // 将uint*_t打包成guid_t
      void unpack(const guid_t in, Guid &guid); // 将guid_t解包
      bool operator==(const Guid& guid); // 相同返回true,不相同返回false
}; 

} // namespace utils
} // namespace ndsl
#endif // __GUID_H__
