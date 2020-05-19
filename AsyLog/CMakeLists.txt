cmake_minimum_required(VERSION 3.10.0)
PROJECT(TIME)
option(sub "enable subdirector" ON)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    message(STATUS "enable -std=c++11")
endif()

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXX_FLAGS} -O0 -Wall -g -lpthread")


IF(sub)
    MESSAGE(STATUS "YUAN")
    ADD_SUBDIRECTORY(src)
ENDIF()