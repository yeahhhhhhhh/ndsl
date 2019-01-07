<<<<<<< HEAD
/**
 * @file temp_define.h
 * @brief
 * 定义一些变量，正式commit时，可删去
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_DEFINE_H__
#define __NDSL_NET_DEFINE_H__

#include <stdio.h>
#define S_OK 1
#define S_FAIL -1

#define LEVEL_DEBUG 1
#define LEVEL_ERROR 2
#define LEVEL_INFO 3
#define MAXLINE 1024

#define SERV_PORT 9877
#define SA struct sockaddr
#define LISTENQ 1024

#define LOG(level, format, ...) printf(format, ##__VA_ARGS__)

=======
/**
 * @file temp_define.h
 * @brief
 * 定义一些变量，正式commit时，可删去
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NDSL_NET_DEFINE_H__
#define __NDSL_NET_DEFINE_H__

#define MAXLINE 16384

#define SERV_PORT 9877
#define SA struct sockaddr
#define LISTENQ 1024

>>>>>>> dev_gyz
#endif // __NDSL_NET_DEFINE_H__