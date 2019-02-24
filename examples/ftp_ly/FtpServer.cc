// /**
//  * @file FtpServer.cc
//  * @brief
//  *
//  * @author lanry
//  * @email luckylanry@163.com
//  */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include "Protbload.pb.h"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/Entity.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/config.h"

using namespace ndsl;
using namespace net;
using namespace Protbload;

#define BUFSIZE 2048
#define RANDOMPORT 1314


bool FalgError = false;
static void tcpConnectionisError(int a, Channel *c)
{
    FalgError = true;
}

bool acceptFlag =false;
static  void tcpAccept(void *aa){
    acceptFlag = true;
}

TcpConnection* sConn;
struct SocketAddress4 ftpsrvaddr;
TcpAcceptor *tAc;

// receive cmd and responce
static int response(TcpConnection* sConn)
{
	int status;
    char recvbuf[BUFSIZE];
    ssize_t len1;
    sConn->onRecv(recvbuf,&len1,0,NULL,NULL);
	if(strcmp(recvbuf,"QUIT")==0)
    {
        status =221;
    }
	else if(strcmp(recvbuf,"PASV")){
        status = 227;
        ftpsrvaddr.setPort(RANDOMPORT);
    }else{
        status = 502;
    }
	return status;
}


int main(int argc,char **argv)
{
    set_ndsl_log_sinks(LOG_SOURCE_ALL, LOG_OUTPUT_TER);
    if(argc < 2)
    {
        fprintf(stderr, "Usage: server <address> <port>\n");
    }else{

        //初始化EPOLL
        EventLoop loop;
        int s = loop.init();
        if(s < 0) {printf("loop init fail!\n"); }

        //地址结构
        //static_cast<unsigned short>(atoi(argv[2]))
        struct SocketAddress4 servaddr(
            argv[1],static_cast<unsigned short>(atoi(argv[2])));
        tAc = new TcpAcceptor(&loop);
        s = tAc->start(servaddr);

        struct sockaddr_in rservaddr;
        bzero(&rservaddr,sizeof(rservaddr));
        socklen_t addrlen;
      
        sConn = new TcpConnection();
        sConn->onError(tcpConnectionisError);
        tAc->onAccept(
            sConn,(struct sockaddr *)&rservaddr,&addrlen,tcpAccept,sConn);
        //  responce cmd request

        int stat= response(sConn);
        printf("%d\n",stat);
        EventLoop::loop(&loop);

    }
    return 0;
}
