// /**
//  * @file FtpServer_.cc
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
int clientid = 1025;
int serverid = 21;

bool FalgError = false;
static void tcpConnectionisError(int a, Channel *c)
{
    FalgError = true;
}

struct SocketAddress4 ftpsrvaddr;
TcpAcceptor *tAc;
// receive cmd and responce
// static int response(int fd,char cmd[])
// {
// 	int status;
// 	if(-1==recv(fd,cmd,strlen(cmd),0))
//     {
//         return S_FALSE;
//     }
// 	if(strcmp(cmd,"QUIT")==0)
//     {
//         status =221;
//     }
// 	else if(strcmp(cmd,"PASV")){
//         status = 227;
//         ftpsrvaddr.setPort(RANDOMPORT);
//     }else{
//         status = 502;
//     }
// 	return status;
// }

static void servercallback(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    Protbload::ADD *addmessage = new Protbload::ADD;
    addmessage->ParseFromString(data);
    printf("agv1:%d  agv2:%d \n", addmessage->agv1(), addmessage->agv2());

    std::string fstr;
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->set_answer(addmessage->agv1() + addmessage->agv2());
    printf("argv1 and argv2 of ADD: %d  %d\n",addmessage->agv1(),addmessage->agv2());
    printf("result == %d \n", resultmessage->answer());
    resultmessage->SerializeToString(&fstr);
    int flen = fstr.size();
    Multiplexer->sendMessage(clientid , flen, fstr.c_str());
}

static void onConn(void * para)
{
    TcpConnection *conn = (TcpConnection *) para;
    Multiplexer *servermulti = new Multiplexer(conn);

    Entity *server = new Entity(serverid, servercallback, servermulti);
    server->pri();

    TcpConnection *con1 = new TcpConnection();
    tAc->onAccept(con1, NULL, NULL, onConn, con1);
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
      
        TcpConnection* conn = new TcpConnection();
        conn->onError(tcpConnectionisError);
        tAc->onAccept(
            conn,(struct sockaddr *)&rservaddr,&addrlen,onConn,conn);
        EventLoop::loop(&loop);

    }
    return 0;
}
