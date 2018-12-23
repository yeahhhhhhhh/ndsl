/**
 * @file TcpClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "ndsl/utils/temp_define.h"

// TODO: 用来模拟用户？

int main()
{
    int listenfd;
    int n;
    char buf[MAXLINE], recv[MAXLINE];
    listenfd = init(CLIENT, argv[1]);

    for (;;) {
        if ((n = Read(fileno(stdin), buf, MAXLINE)) > 0)
            Write(listenfd, buf, n);
        else if (n == 0)
            break;

        if ((n = Read(listenfd, recv, MAXLINE)) > 0)
            Write(fileno(stdout), recv, n);
    }

    return 0;
}
