cmake_minimum_required(VERSION 3.6)
project(lab02_shared_memory)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    childProc.c
    ipcEx.h
    mainProc.c)

add_executable(lab02_shared_memory ${SOURCE_FILES})