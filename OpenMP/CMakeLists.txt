cmake_minimum_required(VERSION 3.8)
project(OpenMPBarrier)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c gtmp_tree_barrier.c)
add_executable(OpenMPBarrier ${SOURCE_FILES})