////
// @file Log.cc
// @brief
// 实现日志
//
// @author niexw
// @email xiaowen.nie.cn@gmail.com
//
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdarg.h>
#include "ndsl/utils/Log.h"
#include "ndsl/utils/TimeStamp.h"

////
// @brief
// log接口
//
struct ILog
{
    virtual void log(const char *data,const char*path, size_t size) = 0;
};

////
// @brief
// 日志sinker
//
struct LogSinker
{
    ILog *M_sinks[2]; // log sink
    int M_level;      // log级别

  public:
    LogSinker()
        : M_level(LOG_DEBUG_LEVEL)
    {
        M_sinks[0] = NULL;
        M_sinks[1] = NULL;
    }
    // 不需要析构函数
};

////
// @brief
// 文件sinker
//
class FileLogSinker : public ILog
{
  private:
    int M_file; // log文件描述符
    static const off_t MAX_LOG_FILE_SIZE = 1024 * 1024 * 4; // 16M

  public:
    FileLogSinker()
        : M_file(-1)
    {}
    ~FileLogSinker()
    {
        if (M_file != -1) ::close(M_file);
    }

    void log(const char *data,const char* path, size_t size)
    {
        M_file = ::open(path,
                         O_WRONLY | O_APPEND | O_CREAT,
                         0620);   
        ::write(M_file, data, size);
        check_size();
    }

  private:
    void check_size()
    {
        struct stat state;
        ::fstat(M_file, &state);
        if (state.st_size > MAX_LOG_FILE_SIZE) {
            ::close(M_file);
        }
    }
};

////
// @brief
// syslog sinker
//
class SysLogSinker : public ILog
{
  public:
    void log(const char *data, const char*path,size_t size) { ::syslog(LOG_USER, "%s", data); }
};

////
// @brief
// 全局logger
//
static LogSinker S_logger;
static FileLogSinker S_file_sinker;
static SysLogSinker S_syslog_sinker;

void set_ndsl_log_sinks(int sinks)
{
    if (sinks & LOG_SINK_FILE) {
        S_logger.M_sinks[0] = &S_file_sinker;
    } else
        S_logger.M_sinks[0] = NULL;

    if (sinks & LOG_SINK_SYSLOG) {
        S_logger.M_sinks[1] = &S_syslog_sinker;
    } else
        S_logger.M_sinks[1] = NULL;
}
void set_ndsl_log_level(int level) { S_logger.M_level = level; }

void ndsl_log_into_sink(int level, const char* path,const char *format, ...)
{
    // 检查log级别
    if (level < S_logger.M_level) return;
    char buffer[4096];

    // file log
    if (S_logger.M_sinks[0]) {
        TimeStamp ts;
        ts.now();
        buffer[0] = '[';
        ts.to_string(buffer + 1, 4096);
        int ret1 = ::strlen(buffer);
        buffer[ret1] = ']';

        int ret2 = sprintf(
            buffer + ret1 + 1,
            " lv=%d pid=%d tid=%lx ",
            level,
            ::getpid(),
            (long) ::pthread_self()); // 毫秒

        // 复制数据
        va_list ap;
        va_start(ap, format);
        int ret3 = vsnprintf(
            buffer + ret1 + ret2 + 1, 512 - ret1 - ret2 - 1, format, ap);
        if (ret3 >= 0)
            S_logger.M_sinks[0]->log(buffer, path,ret1 + ret2 + ret3 + 1);
        va_end(ap);

    }

    // syslog
    if (S_logger.M_sinks[1]) {
        int ret2 = sprintf(
            buffer,
            "lv=%d pid=%d tid=%lx ",
            level,
            ::getpid(),
            (long) ::pthread_self()); // 毫秒
       

        // 复制数据
        va_list ap;
        va_start(ap, format);
        int ret3 = vsnprintf(buffer + ret2, 512 - ret2, format, ap);
        if (ret3 >= 0) S_logger.M_sinks[1]->log(buffer, path,ret2 + ret3);
        va_end(ap);

    }
}
