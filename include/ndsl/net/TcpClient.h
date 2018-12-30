/**
 * @file TcpClient.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__

namespace ndsl {
namespace net {

class TcpClient
{
  public:
    // 与服务器建立连接
    int onConnect();
};

} // namespace net
} // namespace ndsl

#endif // __TCPCLIENT_H__