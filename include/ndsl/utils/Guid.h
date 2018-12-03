////
// @file Guid.h
// @brief
// Guid类
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
      
    private:
      guid_t gu;
    
    public:
      int generate(); // 生成guid
      int toString(char* str); // 将guid_t转换成字符串
      int toGuid_t(char* str); // 将字符串转成guid_t
      bool operator==(Guid& guid); // 相同返回true,不相同返回false
      bool operator<(Guid& guid); // 小于返回true
      bool operator>( Guid& guid); // 大于返回true
}; 

} // namespace utils
} // namespace ndsl
#endif // __GUID_H__
