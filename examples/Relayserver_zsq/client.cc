/**
 * @file client.cc
 * @brief
 *
 * @author zsq
 * @email 1575033031@qq.com
 */


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>

#define BUFSIZE 9
size_t bytesRead;
char cbuf[BUFSIZE];
char recvbuf[BUFSIZE];

void makeMessage()
{
    int i = 0;
    for (i = 0; i < BUFSIZE; ++i) {
        cbuf[i] = '1';
    }
    cbuf[i] = '\n';
}
int main(int argc,char **argv)
{
    int sockfd_; 
    struct sockaddr_in servaddr;
    
    sockfd_ =  socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd_ < 0)
    {
        printf("socket error!\n");
        return 0 ;
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    int n;
    if ((n = connect(sockfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0) {
        if (errno != EINPROGRESS) {
            printf("TcpClient::onConnection connect fail\n");
            return 0;
        }
    }

    makeMessage();

    memset(recvbuf, 0, sizeof(recvbuf));
    bytesRead = 0;
    bool isEnd = false;
    int count = 0;
    size_t n1, n2;

    while (!isEnd) {
        printf("cbuf = %s\n",cbuf);
        n1 = write(sockfd_, cbuf, strlen(cbuf));
        if (n1 < 0) {
            printf("write error\n");
            isEnd = true;
        } else {
            n2 = read(sockfd_, recvbuf, BUFSIZE);
            if (n2 < 0) {
                printf("read error\n");
                isEnd = true;
            } else {
                write(fileno(stdout),recvbuf,n2);
                memset(recvbuf, 0, sizeof(recvbuf));
                count++;
                printf("count = %d\n",count);
            }
        }
        if(count > 10) isEnd = true;
    }
    return 0;
}