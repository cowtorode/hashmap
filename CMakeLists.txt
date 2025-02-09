cmake_minimum_required(VERSION 3.30)
project(CTest C)

set(CMAKE_C_STANDARD 23)

add_executable(CTest main.c
        map.c
        map.h)
