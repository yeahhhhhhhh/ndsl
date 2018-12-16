#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "SocketAddress.h"

namespace ndsl{
namespace net{

const size_t IPV4LEN = 15;   
const size_t IPV6LEN = 39;   
const size_t MAXSOCKADDRLEN = 100;
const char* ANYADDR = "0";
const char* IPV4_ANYADDR = "0.0.0.0"; // 原基类是 "0.0.0"
const char* IPV6_ANYADDR = "::"; // 原基类是 "::1"


SocketAddress4::SocketAddress4()
{
	sin_port = 0;
	sin_addr.s_addr = htonl(INADDR_ANY); 
}

SocketAddress6::SocketAddress6()
{
	sin6_port = 0;
	sin6_addr = in6addr_any; 
}

SocketAddress4::SocketAddress4( const char* buf, unsigned short p )
{
    
	sin_family = AF_INET;
	sin_port = p;
    if ( strlen( buf ) > IPV4LEN || strcmp( buf, ANYADDR ) == 0 ) // ip要是大于255了需要处理吗？
    {
        sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        inet_pton(AF_INET, buf, &sin_addr);
    }   
}

SocketAddress6::SocketAddress6( const char* buf, unsigned short p )
{
    
	sin6_family = AF_INET6;
	sin6_port = p;   
	if ( strlen( buf ) > IPV6LEN || strcmp( buf, ANYADDR ) == 0 )    // ip要是大于ffff了需要处理吗？ 
	{
		sin6_addr = in6addr_any; 
	}
	else
	{
		inet_pton(AF_INET6, buf, &sin6_addr);
	}
}

SocketAddress4::~SocketAddress4()
{
}

SocketAddress6::~SocketAddress6()
{
}

void SocketAddress4::setPort( unsigned short p )
{
    sin_port = p;
}

void SocketAddress6::setPort( unsigned short p )
{
    sin6_port = p;
}

void SocketAddress4::setAddress( const char* buf, unsigned short p )
{
    
	sin_family = AF_INET;
	sin_port = p;
    {
        if ( strlen( buf ) <=  IPV4LEN && strcmp( buf, ANYADDR ) != 0 )   
        {
            inet_pton(AF_INET, buf, &sin_addr);
        }
    }
}

void SocketAddress6::setAddress( const char* buf, unsigned short p )
{
    
	sin6_family = AF_INET6;
	sin6_port = p;
	if ( strlen( buf ) <= IPV6LEN && strcmp( buf, ANYADDR ) != 0 )   
	{
		inet_pton(AF_INET6, buf, &sin6_addr);
	}
}

const char* SocketAddress4::getIP( void )const
{
	char str[INET_ADDRSTRLEN];
	return inet_ntop(AF_INET, &sin_addr, str, sizeof(str)); //need fix
}

const char* SocketAddress6::getIP( void )const
{
	char str[INET6_ADDRSTRLEN];
	return inet_ntop(AF_INET, &sin6_addr, str, sizeof(str)); //need fix
}

unsigned short SocketAddress4::getPort( void )const
{
	return sin_port;
}

unsigned short SocketAddress6::getPort( void )const
{
	return sin6_port;
}
	
string& SocketAddress4::convertToString( void ) 
{
	static string str;
    char buf[ MAXSOCKADDRLEN ] = { 0 };
    sprintf( buf, "%s %u", inet_ntop(AF_INET, &sin_addr, buf, 
	sizeof(buf)), sin_port );
	str = buf;
    return str;
}

string& SocketAddress6::convertToString( void ) 
{
	static string str;
    char buf[ MAXSOCKADDRLEN ] = { 0 };
    sprintf( buf, "%s %u", inet_ntop(AF_INET6, &sin6_addr, buf, 
	sizeof(buf)), sin6_port );
	str = buf;
    return str;
}

bool SocketAddress4::operator == ( const SocketAddress4& h )const
{
    if ( sin_addr.s_addr == h.sin_addr.s_addr && sin_port == h.sin_port )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SocketAddress6::operator == ( const SocketAddress6& h )const
{
    if ( strcmp((char*)sin6_addr.s6_addr, (char*)h.sin6_addr.s6_addr ) == 0 && 
	sin6_port == h.sin6_port )
    {
        return true;
    }
    else
    {
        return false;
    }
}

SocketAddress4& SocketAddress4::operator=( const SocketAddress4& h )             
{
    sin_family = h.sin_family;
	sin_addr.s_addr = h.sin_addr.s_addr;
    sin_port = h.sin_port;
    return *this;  
}  
                    
SocketAddress6& SocketAddress6::operator=( const SocketAddress6& h )             
{
    sin6_family = h.sin6_family;
	memcpy(sin6_addr.s6_addr, h.sin6_addr.s6_addr, 16);
    sin6_port = h.sin6_port;
    return *this;  
}
            
sockaddr_in SocketAddress4::getAddr()
{
    struct sockaddr_in addr;
    memset( &addr, 0, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = sin_addr.s_addr;
    addr.sin_port = htons( sin_port );
    return addr;
}

sockaddr_in6 SocketAddress6::getAddr()
{
    struct sockaddr_in6 addr;
    memset( &addr, 0, sizeof( addr ) );
    addr.sin6_family = AF_INET6;
    memcpy(addr.sin6_addr.s6_addr,  sin6_addr.s6_addr, 16);
    addr.sin6_port = htons( sin6_port );
    return addr;
}

bool SocketAddress4::getAddr( sockaddr_in& addr )
{
    if (sin_port > 0)
	{
		memset( &addr, 0, sizeof( addr ) );
		addr.sin_family = AF_INET;
		addr.sin_port = htons( sin_port );
		addr.sin_addr.s_addr = sin_addr.s_addr;
		return true;
	}
	else return false;
}

bool SocketAddress6::getAddr( sockaddr_in6& addr )
{
    if (sin6_port > 0)
	{
		memset( &addr, 0, sizeof( addr ) );
		addr.sin6_family = AF_INET6;
		addr.sin6_port = htons( sin6_port );
		memcpy(addr.sin6_addr.s6_addr, sin6_addr.s6_addr, 16);
		return true;
	}
	else return false;
}
}	// namespace net
}	// namespace ndsl
