/**
 * @file client.cc
 * @brief
 *
 * @author lanry
 * @email luckylanry@163.com
 */

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
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/config.h"

using namespace ndsl;
using namespace net;
using namespace Protbload;

#define BUFSIZE 2048
#define CMDPORT 21
#define RANDOMPORT 1314
int clientid = 1025;
int serverid = 21;

struct SocketAddress4 ftpservaddr;
int sockfd;
EventLoop loop;

// // client connect server
// int start()
// {
//     ftpservaddr.setPort(CMDPORT);
//     // bzero(&ftpservaddr,sizeof(SocketAddress4));
//     ndsl::net::TcpClient *cli = new ndsl::net::TcpClient();
//     ndsl::net::TcpConnection *conn = cli->onConnect(&loop,true,&ftpservaddr);
//     sockfd = cli->sockfd_ ;
//     return S_OK;
// }

// client send a command request
// int sendRequest(char cmd[])
// {   
//     int length;
//     length = send(sockfd, cmd, strlen(cmd), 0);
//     //send函数通过sockfd接口发送cmd，发送成功返回发送的字节数  
//     if (length <= 0)
//     {
//         printf("send cmd error ! \n");
//         return S_FALSE; 
//     }
//     return S_OK;  
// }
// // receive server's responce
// char *recvReply(int sockfd,int status,struct SocketAddress4 ftpservaddr)
// {   
//     int status =0;
//     char recvbuf[BUFSIZE];
//     char IpBuf[1024];
//     status= recv(sockfd,recvbuf,BUFSIZE,0);
//     // cmd concerning interpretion
//     switch(status)
//     {
// 	    case 220: { return "server ready.\n"; }
//         case 200: { return "dispose commmand\n" ;}
//         case 221: { return "exit\n";}
//         case 502: { return "cmd send fail,not legally cmd \n " ;}
// 		case 226: { return "request file success\n"; }
//         case 227: {
//              return "send PASV mode success\n"; 
//               // get server IP and address
//              ftpservaddr.getIP(IpBuf);
//              unsigned short port = ftpservaddr.getPort();
//              printf("server's port is:",port);
//              }
//         default: { return "S_FALSE" ;}
//     }
//     return recvbuf;
// }
// // send data connection
// int dataConn(int dataConnfd)
// {
//     ftpservaddr.setPort(RANDOMPORT);
//     ndsl::net::TcpClient *cli = new ndsl::net::TcpClient();
//     ndsl::net::TcpConnection *conn = cli->onConnect(&loop,true,&ftpservaddr);
//     dataConnfd = cli->sockfd_ ;
// 	int ack = 1;
// 	//给服务器发送一个确认，告诉服务器客户端创建好了一条数据链路
// 	if(send(dataConnfd,(char*)&ack,sizeof(ack),0)<0) 
// 	{
// 		printf("client:ack write error:%d\n",errno);
// 		return S_FALSE;
// 	}
// 	return dataConnfd;     
// }
// int ftp_upload(char* localfile,char* remotepath,char* remotefilename)
// {
//     char send[BUFSIZE];
    
//     return 0; 
// }

// static int ftp_download(char *localfile,char* remotefile)
// {

// }
static void clientcallback(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->ParseFromString(data);
    printf("result==%d \n", resultmessage->answer());
}

int main(int argc,char **argv)
{
    set_ndsl_log_sinks(LOG_SOURCE_ALL, LOG_OUTPUT_TER);
    if(argc < 2){
        fprintf(stderr,"Usage: %s <address> <port> \n",argv[0]);
    }else{  
        //初始化EPOLL
        EventLoop loop;
        loop.init();
        //地址结构
        struct SocketAddress4 servaddr(
            argv[1],static_cast<unsigned short>(atoi(argv[2])));
        // start a client
        TcpConnection *conn;
        TcpClient* pCli = new TcpClient();
        conn = pCli->onConnect(&loop, true, &servaddr);
        if(conn == NULL)
        {
            printf("conn == NULL!\n");
        }

        Multiplexer *clientmulti = new Multiplexer(conn);
        Entity *client = new Entity(clientid, clientcallback, clientmulti);

        int a, b;
        printf("input the agv1 and agv2 of ADD: \n");
        scanf("%d %d", &a, &b);
        std::string pstr;
        Protbload::ADD *addmessage = new Protbload::ADD;
        addmessage->set_agv1(a);
        addmessage->set_agv2(b);
        addmessage->SerializeToString(&pstr);
        int mlen = pstr.size();
   
        client->multiplexer_->sendMessage(serverid, mlen, pstr.c_str());

        printf("after sendmessage!\n");

        loop.loop(&loop);

    }
    return 0;
}

