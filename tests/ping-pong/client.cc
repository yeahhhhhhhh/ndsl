/**
 * @file client.cc
 * @brief
 *  TODO: 客户端是否也要用到网络库
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/EventLoop.h"

#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/time.h>

#define BUFSIZE 1024

using namespace ndsl;
using namespace net;

size_t bytesRead;
char cbuf[BUFSIZE];
int64_t mtime;

void onDisconnect()
{
    printf(
        "%lf MiB/s throughput\n",
        (static_cast<double>(bytesRead) * 1000000.0) / (mtime * 1024 * 1024));
}

void makeMessage()
{
    for (int i = 0; i < BUFSIZE; ++i) {
        cbuf[i] = static_cast<char>(1);
    }
}

int main(int argc, char *argv[])
{
    // 启动服务
    // 初始化EPOLL
    EventLoop loop;
    loop.init();

    // 启动一个客户端
    TcpClient *pCli = new TcpClient();
    pCli->onConnect();

    // 构造传输数据
    makeMessage();

    bytesRead = 0;
    bool isEnd = false;
    size_t n1, n2;
    struct timeval t1, t2;
    while (!isEnd) {
        gettimeofday(&t1, NULL);
        if ((n1 = write(pCli->sockfd_, cbuf, strlen(cbuf))) < 0) {
            isEnd = true;
        } else {
            if ((n2 = read(pCli->sockfd_, cbuf, BUFSIZE)) < 0) {
                isEnd = true;
            } else {
                bytesRead += n2;
            }
        }
    }
    gettimeofday(&t2, NULL);

    mtime = (t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec;

    // 计算
    onDisconnect();

    return 0;
}
