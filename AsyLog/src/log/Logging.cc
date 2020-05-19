
#include "Logging.h"
#include <string.h>
#include <stdarg.h>
#include <iostream>


//TODO：增加异步日志文件
void defaultOut(const char* msg, int len)
{
    ::fwrite(msg, 1, len, stdout);
}

Logger::OutputFunc g_output = defaultOut;

const char* LogLevelName[Logger::NUM_LOG_LEVELS]=
{
    "TRACE ",
    "DEBUG ",
    "INFO  ",
    "WARN  ",
    "ERROR ",
    "FATAL ",
};


Logger::Impl::Impl(Logger::LogLevel level, const char* fileName, int line, const char* func)
:level_(level),
 line_(line),
 func_(func)
{
    formatTime();
    //TODO:添加线程号日志
    const char* slash = strrchr(fileName, '/');  //strrchr获取最后一个/的位置
    if (slash)
    {
        basename_ = slash + 1;
    }
}

void Logger::Impl::formatTime()
{
    struct tm tm_time = {0};
    time_t ti = time(NULL);
    gmtime_r(&ti, &tm_time);
    snprintf(time_, 64, "%4d%02d%02d-%02d:%02d:%02d   ",
        tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
        tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
}


Logger::Logger(const char* fileName, int line, LogLevel level)
:impl_(level, fileName, line, NULL)
{
    buffer_.append(LogLevelName[impl_.level_], 6); //级别默认6个字节
    buffer_.append(impl_.time_, strlen(impl_.time_) + 1);
    buffer_.append(impl_.basename_, strlen(impl_.basename_));
}

Logger::Logger(const char* fileName, int line, const char* func, LogLevel level)
:impl_(level, fileName, line, func)
{
   // std::cout<<impl_.time_<<" "<<impl_.func_<<" "<<impl_.basename_<<std::endl;
    buffer_.append(LogLevelName[impl_.level_], 6); //级别默认6个字节
    buffer_.append(impl_.time_, strlen(impl_.time_));
    buffer_.append(impl_.func_, strlen(impl_.func_));
    buffer_.append("  ", 2);
    buffer_.append(impl_.basename_, strlen(impl_.basename_));
}

void Logger::SetOutPut(OutputFunc output)
{
    g_output = output;
}

//析构函数中调用日志写入函数
Logger::~Logger()
{
    g_output(buffer_.data(), buffer_.length());
}

//将日志写进中转buffer
void Logger::stream(const char* fmt...)
{
    int len = 0;
    va_list args;
    va_start(args, fmt);
    len += vsnprintf(buffer_.current(), buffer_.avail(), fmt, args);
    buffer_.add(len);
    va_end(args);
    // std::cout<<buffer_.data();
}
