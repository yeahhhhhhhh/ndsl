/**
 * @file UdpClient.h
 * @brief
 *
 * @author lanry
 * @email  luckylanry@163.com
 */
#ifndef __UDPCLIENT_H__
#define __UDPCLIENT_H__

namespace ndsl {
namespace net {

class UdpClient
{
  public:
    int sockfd_; //用来保存链接fd
    int start();
};

} // namespace net
} // namespace ndsl

#endif // __UDPCLIENT_H__