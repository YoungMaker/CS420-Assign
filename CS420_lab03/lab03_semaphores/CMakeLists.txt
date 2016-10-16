cmake_minimum_required(VERSION 3.6)
project(lab03_semaphores)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    fileWriter.c
    main.c
    utils.c
    utils.h)

add_executable(lab03_semaphores ${SOURCE_FILES})