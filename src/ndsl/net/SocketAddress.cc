#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ndsl/net/SocketAddress.h"

namespace ndsl{
namespace net{

const size_t IPV4LEN = 15;   
const size_t IPV6LEN = 39;   
const size_t MAXSOCKADDRLEN = 100;
const int IPV4 = 4;
const int IPV6 = 6;
const char* ANYADDR = "0";
const char* IPV4_ANYADDR = "0.0.0.0"; // 原基类是 "0.0.0"
const char* IPV6_ANYADDR = "::"; // 原基类是 "::1"

int SocketAddress::ipType = IPV4;

SocketAddress::SocketAddress():
    port_( 0 ), str_( "" )
{
    if ( ipType == IPV4 )
    {
        ip_ = IPV4_ANYADDR;
    }
    else
    {
        ip_ = IPV6_ANYADDR;
    }
}

SocketAddress::SocketAddress( const char* buf, unsigned short p )
{
    port_ = p;
    if ( ipType == IPV4 )
        if ( strlen( buf ) > IPV4LEN || strcmp( buf, ANYADDR ) == 0 ) // ip要是大于255了需要处理吗？
        {
            ip_ = IPV4_ANYADDR;
        }
        else
        {
            ip_ = string( buf );
        }
    else
    {
        if ( strlen( buf ) > IPV6LEN || strcmp( buf, ANYADDR ) == 0 )    // ip要是大于ffff了需要处理吗？ 
        {
            ip_ = IPV6_ANYADDR;
        }
        else
        {
            ip_ = string( buf );
        }
    }
}

SocketAddress::~SocketAddress()
{
}

void
SocketAddress::setPort( unsigned short p )
{
    port_ = p;
}

void
SocketAddress::setAddress( const char* buf, unsigned short p )
{
    port_ = p;
    if ( ipType == IPV4 )
    {
        if ( strlen( buf ) <= IPV4LEN && strcmp( buf, ANYADDR ) != 0 )   
        {
            ip_ = string( buf );
        }
    }
    else
    {
        if ( strlen( buf ) <=  IPV6LEN && strcmp( buf, ANYADDR ) != 0 )   
        {
            ip_ = string( buf );
        }
    }
}

string&
SocketAddress::convertToString( void )
{
    char buf[ MAXSOCKADDRLEN ] = { 0 };
    sprintf( buf, "%s %u", ip_.c_str(), port_ );
    str_ = buf;
    return str_;
}

bool
SocketAddress::ifAnyAddr( void )const
{
    if ( ipType == IPV4 )
        if ( IPV4_ANYADDR == ip_ )
        {
            return true;
        }
        else
        {
            return false;
        }
    else if ( IPV6_ANYADDR == ip_ )
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool
SocketAddress::operator == ( const SocketAddress& h )const
{
    if ( ip_ == h.ip_ && port_ == h.port_ )
    {
        return true;
    }
    else
    {
        return false;
    }
}

SocketAddress&
SocketAddress::operator=( const SocketAddress& h )             
{
    ip_ = h.ip_;
    port_ = h.port_;
    str_ = "";
    return *this;  
}                      

sockaddr_in SocketAddress::getAddr()
{
    struct sockaddr_in addr;
    memset( &addr, 0, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr( ip_.c_str() );
    addr.sin_port = htons( port_ );
    return addr;
}

bool SocketAddress::getAddr( sockaddr_in& addr )
{
    memset( &addr, 0, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port_ );
    return inet_pton( 
        AF_INET, ip_.c_str(), &addr.sin_addr ) == 1 ? true : false;
}
}	// namespace net
}	// namespace ndsl
