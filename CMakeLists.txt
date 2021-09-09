cmake_minimum_required(VERSION 3.20)
project(merge_ch_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(merge_ch_3
        Clock.h
        improved_merge.cpp
        improved_merge.h)
