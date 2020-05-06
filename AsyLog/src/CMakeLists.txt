cmake_minimum_required(VERSION 2.8.7)
SET(SRC_LIST time.cc)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(time ${SRC_LIST})
#链接动态库和可执行文件
TARGET_LINK_LIBRARIES(time libevent.so)
