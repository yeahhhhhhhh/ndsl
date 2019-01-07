////
// @file Log.h
// @brief
// plugin 实现
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include "ndsl/utils/Plugin.h"

#if defined(__cplusplus)
extern "C" {
#endif

int ndsl::utils::Plugin::doit(functype func,int  para)
{
    if(func)
    {
        return (*func)(para);
    }
    return -1;
}

#if defined(__cplusplus)
}
#endif