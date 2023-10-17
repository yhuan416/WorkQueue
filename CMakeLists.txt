cmake_minimum_required(VERSION 3.5)

set(LIB_NAME WorkQueue)

project(WorkQueue)

add_library(${LIB_NAME} STATIC src/WorkQueue.c src/WorkQueueImpl.c)
target_include_directories(${LIB_NAME} PUBLIC include)
target_include_directories(${LIB_NAME} PRIVATE private_include)
