#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include "ndsl/utils/Plugin.h"
#include "ndsl/utils/Log.h"

using namespace std;


typedef Plugin *(*Creat)(int );
void  func(void * para)
{
    std::cout << "hello world!\n " << std::endl;
}

int main(int argc,char **argv)
{
    void * p = NULL;
    Plugin1 * plugin = NULL;
    void * para = NULL;
    p = dlopen("/home/user/Desktop/ndsl/build/bin/libplugin.so", RTLD_NOW | RTLD_DEEPBIND);
    if(!p)
    {
        cout << "cannot open library: " << dlerror() << endl;
        return -1;
    }
    Creat fun = (Creat)dlsym(p,"CreatPlugin");
    if(!fun)
    {
        cout << "cannot load sysbol:  " << dlerror() << endl;
        dlclose(p);
        return -1;
    }
    plugin = (Plugin1*)fun(1);
    if(!plugin)
    {
        printf("plugin == NULL !\n");
    }
    plugin->doit(func,para);
}


