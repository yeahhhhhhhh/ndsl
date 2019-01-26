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

int clientid = 1025;
int serverid = 21;

// struct SocketAddress4 ftpservaddr;
// int sockfd;
// EventLoop loop;


static void clientcallback(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->ParseFromString(data);
    printf("result==%d \n", resultmessage->answer());
}

int main(int argc,char **argv)
{
    set_ndsl_log_sinks(LOG_SOURCE_ALL, LOG_OUTPUT_TER);
    if(argc < 1){
        fprintf(stderr,"Usage: %s <address>\n",argv[0]);
    }else{  
        //初始化EPOLL
        EventLoop loop;
        loop.init();
        //地址结构
        struct SocketAddress4 servaddr(
            argv[1],static_cast<unsigned short>(21));
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

