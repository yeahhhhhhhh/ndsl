/**
 * @file Serverplugin.h
 * @brief
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#ifndef __NDSL_NET_SERVERPLUGIN_H__
#define __NDSL_NET_SERVERPLUGIN_H__

#include "ndsl/utils/Plugin.h"

struct Server : Plugin
{
    int doit(functype func, void *para) {}
    void add(int i) { printf("server result = %d \n", i + 1); }
};

#endif // __NDSL_NET_SERVERPLUGIN_H__