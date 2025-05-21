cmake_minimum_required(VERSION 3.30)
project(map_navigator)

set(CMAKE_CXX_STANDARD 20)

add_executable(map_navigator main.cpp
        graph.cpp
        graph.h
)
