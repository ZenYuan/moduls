cmake_minimum_required(VERSION 3.10.0)
SET(SRC_LIST LogTest.cc)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(LogTest ${SRC_LIST})
#链接动态库和可执行文件
#TARGET_LINK_LIBRARIES(LogTest libevent.so)
