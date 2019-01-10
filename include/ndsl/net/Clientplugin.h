/**
 * @file Clientplugin.h
 * @brief
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#ifndef __NDSL_NET_CLIENTPLUGIN_H__
#define __NDSL_NET_CLIENTPLUGIN_H__

#include "ndsl/utils/Plugin.h"

struct Client : Plugin
{
    int doit(functype func, void *para) {}
    void add(int i) { printf("result = %d \n", i + 1); }
};

#endif // __NDSL_NET_CLIENTPLUGIN_H__