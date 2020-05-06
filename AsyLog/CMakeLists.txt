cmake_minimum_required(VERSION 2.8.7)
PROJECT(TIME)
option(sub "enable subdirector" ON)
#set(CMAKE_C_COMPILER "arm-hisiv300-linux-gcc")
SET (CMAKE_BUILD_TYPE "Debug")
set(CXX_FLAGS -std=c++11)
SET (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXX_FLAGS} -O0 -Wall -g ")


IF(sub)
    MESSAGE(STATUS "YUAN")
    ADD_SUBDIRECTORY(src)
ENDIF()