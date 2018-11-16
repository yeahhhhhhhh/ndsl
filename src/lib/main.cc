#include<stdio.h>
#include<string.h>
#include"ndsl/utils/TimeStamp.h"
#include"ndsl/utils/Log.h"
int main(int argc,char**argv)
{
    printf("start a project!\n");
    TimeStamp ts;
    char buf[512];
    ts.now();
    ts.to_string(buf,512);
    printf("%s\n",buf);
    const char *time1 = "2018-12-02 14:40:08.521990";
    ts.from_string(time1);
    set_ndsl_log_sinks(1);
    LOG(LOG_DEBUG_LEVEL, "./test1.log","DEBUG\n");
    LOG(LOG_ERROR_LEVEL, "./test1.log","ERROR\n");
    LOG(LOG_INFO_LEVEL, "./test1.log","INFO\n");
    LOG(LOG_WARN_LEVEL, "./test1.log","WARN\n");
    LOG(LOG_DEBUG_LEVEL, "./test1.log","test,DEBUG\n");


    return 0;
}