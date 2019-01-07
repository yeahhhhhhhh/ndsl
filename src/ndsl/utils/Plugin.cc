////
// @file Log.h
// @brief
// plugin 实现
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include "ndsl/config.h"
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
    return S_FALSE;
}
ndsl::utils::Plugin CreatPlugin()
{
    ndsl::utils::Plugin plugin;
    ndsl::utils::Guid guid;
    plugin.tag = guid.generate();
    return plugin;
}

#if defined(__cplusplus)
}
#endif


