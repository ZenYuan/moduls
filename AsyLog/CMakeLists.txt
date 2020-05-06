cmake_minimum_required(VERSION 3.10.0)
PROJECT(TIME)
option(sub "enable subdirector" ON)
#添加头文件的搜索路径
#INCLUDE_DIRECTORIES(/data2/zhangyuanyuan22/work/project/share/include)
#添加动态库的搜索路径
#LINK_DIRECTORIES(/data2/zhangyuanyuan22/work/project/share/lib)
#指定编译器
#set(CMAKE_CXX_COMPILER "/data2/zhangyuanyuan22/work/usr/local/gcc-8.3.0/bin/g++")
#采用以下方式
#export CC=/data2/zhangyuanyuan22/work/usr/local/gcc-8.3.0/bin/g++
#export CXX=/data2/zhangyuanyuan22/work/usr/local/gcc-8.3.0/bin/g++

SET (CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -lpthread")
SET (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXX_FLAGS} -O0 -Wall -g")


IF(sub)
    MESSAGE(STATUS "YUAN")
    ADD_SUBDIRECTORY(src)
ENDIF()