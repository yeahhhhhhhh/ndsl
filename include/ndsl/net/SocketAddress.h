////
// @file SocketAddress.h
// @brief
// 封装SocketAddress
//
// @author ranxiangjun
// @email ranxianshen@gmail.com
//
#ifndef _SOCKETADDRESS_H_
#define _SOCKETADDRESS_H_

#include <string>
#include <netinet/in.h>

namespace ndsl{
namespace net{

class SocketAddress
{
  public:
    static int ipType; // 默认ipv4类型

  public:
    SocketAddress();
    SocketAddress( const char* buf, unsigned short p );
    ~SocketAddress();

    void setAddress( const char*, unsigned short );
    const char* getIP( void )const
    {
        return ip_.c_str();
    };
    unsigned short getPort( void )const
    {
        return port_;
    };
    sockaddr_in getAddr();
    bool getAddr( sockaddr_in& addr );  
    void setPort( unsigned short );
    string& convertToString( void );
    bool ifAnyAddr( void )const;
    bool operator == ( const SocketAddress& )const;   // 判断两个地址是否相同
    SocketAddress& operator = ( const SocketAddress& ); // 地址的赋值

private:
    string          ip_;
    unsigned short  port_;
    string          str_;
};
}	// namespace net
}	// namespace ndsl

#endif	// _SOCKETADDRESS_H_
