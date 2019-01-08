////
// @file Log.h
// @brief
// plugin 实现
//
// @author zhangsiqi
// @email 1575033031@qq.com
//

#include <stdio.h>
#include "ndsl/config.h"
#include "ndsl/utils/Plugin.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct Plugin1 : Plugin
{
    
    int doit(functype func, int para)
    {
        if (func) { return (*func)(para); }
        return S_FALSE;
    }
};

Plugin *CreatPlugin(int tag)
{
    if (tag == 1) {
        return new Plugin1;
    } else
        return NULL;
}


#if defined(__cplusplus)
}
#endif

