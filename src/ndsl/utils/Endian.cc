////
// @file Endian.cc
// @brief
// 实现大小端的转换
//
// @author lanyue
// @email luckylanry@163.com 
//
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ndsl/utils/Endian.h>

namespace ndsl {
namespace utils {
    // 类型强转，implict_cast只能执行up-cast,派生类->基类
    template<typename To, typename From>
    inline To implicit_cast(From const &f)
    {
      return f;
    }

    // const struct sockaddr_in* ndsl::utils::sockaddr_in_cast(const struct sockaddr* addr)
    // {  
    //     return static_cast<const struct sockaddr_in*>(implicit_cast<const void*>(addr));
    // }

    // const struct sockaddr_in6* ndsl::utils::sockaddr_in6_cast(const struct sockaddr* addr)
    // {
    //       return static_cast<const struct sockaddr_in6*>(implicit_cast<const void*>(addr));
    // }
    
     uint64_t Endian::hToN64(uint64_t host64)
   {
        return htobe64(host64);
   }
     uint32_t Endian::hToN32(uint32_t host32)
   {
        return htobe32(host32);
   }

     uint16_t Endian::hToN16(uint16_t host16)
   {
        return htobe16(host16);
   }

   // uint64_t 的整形数字由网络字节序转化为主句字节序 
     uint64_t nToH64(uint64_t net64)
   {
        return be64toh(net64);
   }

    uint32_t nToH32(uint32_t net32)
   {
       return be32toh(net32);
   }

    uint16_t nToH16(uint16_t net16)
   {
       return be16toh(net16);

   }
    // /* 提取出套接字地址的 ip 点分十进制 */
    // void Endian::toIp(char* buf, size_t size,const struct sockaddr* addr)
    // {
    //     if (addr->sa_family == AF_INET)
    //     {
    //         assert(size >= INET_ADDRSTRLEN);
    //         const struct sockaddr_in* addr4 = sockaddr_in_cast(addr);
    //         /* inet_ntop 将二进制整数转化为点分十进制 */
    //         ::inet_ntop(AF_INET, &addr4->sin_addr, buf, static_cast<socklen_t>(size));
    //      }
    //      else if (addr->sa_family == AF_INET6)
    //      {
    //          assert(size >= INET6_ADDRSTRLEN);
    //          const struct sockaddr_in6* addr6 = sockaddr_in6_cast(addr);
    //          ::inet_ntop(AF_INET6, &addr6->sin6_addr, buf, static_cast<socklen_t>(size));
    //       }
    //  }

    // void Endian::toIpPort(char* buf, size_t size,const struct sockaddr* addr)
    // {
    //     char host[INET_ADDRSTRLEN] = "INVALID"; // INET_ADDRSTRLEN 网际地址的长度
    //     toIp(host, sizeof host,addr);
    //     const struct sockaddr_in* addr2 = sockaddr_in_cast(addr);
    //     uint16_t port = Endian::networkToHost16(addr2->sin_port);
    //     snprintf(buf, size, "%s:%u", host, port);
    // }

    // // 用ip和port构造一个addr
    // void Endian::fromIpPort(const char* ip, uint16_t port,struct sockaddr_in* addr)
    // {
    //   addr->sin_family = AF_INET;
    //   addr->sin_port =Endian::hostToNetwork16(port);
    //   if (::inet_pton(AF_INET, ip, &addr->sin_addr) <= 0)
    //   {
    //      //LOG_SYSERR << "utils::fromIpPort";
    //   }
    //  }

} // namespace utils
} // namespace ndsl