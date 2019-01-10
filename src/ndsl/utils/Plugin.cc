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
<<<<<<< HEAD

Plugin *CreatPlugin(int tag)
{
    // client
=======


Plugin *CreatPlugin(int tag)
{
    //client
>>>>>>> dev_zsq
    if (tag == 1) {
        return new Plugin1;
    } else
        return NULL;
<<<<<<< HEAD
    // server
    if (tag == 2) {
=======
    //server
     if (tag == 2) {
>>>>>>> dev_zsq
        return new Plugin2;
    } else
        return NULL;
}

#if defined(__cplusplus)
}
#endif
<<<<<<< HEAD
=======

>>>>>>> dev_zsq
