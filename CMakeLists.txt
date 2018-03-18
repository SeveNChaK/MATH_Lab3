cmake_minimum_required(VERSION 3.9)
project(ThirdLab)

set(CMAKE_CXX_STANDARD 11)

add_executable(Calc headers/rkf45.h lib/rkf45.cpp third/main.cpp headers/euler.h lib/euler.cpp headers/rk3.h lib/rk3.cpp)
