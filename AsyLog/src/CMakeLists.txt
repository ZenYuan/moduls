cmake_minimum_required(VERSION 3.10.0)
list(APPEND _source log/LogTest.cc event/Channel.cc event/Epoll.cc event/EventLoop.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(LogTest ${_source})
#链接动态库和可执行文件
#TARGET_LINK_LIBRARIES(LogTest libevent.so)
