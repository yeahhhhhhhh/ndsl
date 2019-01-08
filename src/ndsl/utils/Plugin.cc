////
// @file Log.h
// @brief
// plugin 实现
//
// @author zhangsiqi
// @email 1575033031@qq.com
//


#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include "ndsl/config.h"
#include "ndsl/utils/Plugin.h"

ndsl::utils::Plugin CreatPlugin()
{
    ndsl::utils::Plugin plugin;
    ndsl::utils::Guid guid;
    plugin.tag = guid.generate();
    return plugin;
}

int ndsl::utils::Plugin::doit(functype func,int  para)
{
    if(func)
    {
        return (*func)(para);
    }
    return S_FALSE;
}


#if defined(__cplusplus)
}
#endif


