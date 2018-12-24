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

using namespace std;

#include <string>
#include <netinet/in.h>

namespace ndsl{
namespace net{

struct SocketAddress4:sockaddr_in
{
  public:
    SocketAddress4(); // 初始化一个通配地址
    SocketAddress4( const char* buf, unsigned short p ); // 通过字符数组和端口号参数初始化一个地址
    ~SocketAddress4();

    void setAddress( const char*, unsigned short ); // 设置地址
    const char* getIP( void )const; // 获取IP   
    unsigned short getPort( void )const;    
    sockaddr_in getAddr();
    bool getAddr( sockaddr_in& addr );  
    void setPort( unsigned short );
    string& convertToString( void );
    bool operator == ( const SocketAddress4& )const;   // 判断两个地址是否相同
    SocketAddress4& operator = ( const SocketAddress4& ); // 地址的赋值

};

struct SocketAddress6:sockaddr_in6
{
	public:
    SocketAddress6();
    SocketAddress6( const char* buf, unsigned short p );
    ~SocketAddress6();

    void setAddress( const char*, unsigned short );
    const char* getIP( void )const;
    unsigned short getPort( void )const;    
    sockaddr_in6 getAddr();
    bool getAddr( sockaddr_in6& addr );  
    void setPort( unsigned short );
    string& convertToString( void );
    bool operator == ( const SocketAddress6& )const;   // 判断两个地址是否相同
    SocketAddress6& operator = ( const SocketAddress6& ); // 地址的赋值
};
}	// namespace net
}	// namespace ndsl

#endif	// _SOCKETADDRESS_H_
