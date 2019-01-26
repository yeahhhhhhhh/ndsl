////
// @file Ftpclieb.h
// @brief
// 
//
// @author lanry
// @email luckylanry@163.com
//
#ifndef __NDSL_NET_FTPCLIENT_H__
#define __NDSL_NET_FTPCLIENT_H__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/SocketAddress.h"

using namespace ndsl;
using namespace net;

class  FtpClient
{
  private:
    int sockfd;
    char cmd[];
  public:
    FtpClient();
    ~FtpClient();
    int sendRequest(TcpConnection *conn,char cmd[]);
    const char *recvReply(TcpConnection *conn,struct SocketAddress4 ftpservaddr);
    int dataConn(TcpClient *pCli);
    int ftp_upload(char* localfile,char* remotepath,char* remotefilename);
    int ftp_download(char *localfile,char* remotefile);

};

#endif // __NDSL_NET_FTPCLIENT_H__