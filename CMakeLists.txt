cmake_minimum_required(VERSION 3.9)
project(ThirdLab)

set(CMAKE_CXX_STANDARD 11)

set(executable main.cpp)
set(Eler Euler.cpp rkf45.cpp)
add_library(Euler STATIC ${Eler})
add_executable(ThirdLab ${executable})
target_link_libraries(ThirdLab Euler)
