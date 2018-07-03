cmake_minimum_required(VERSION 3.10)
project(srv)

set(CMAKE_CXX_STANDARD 17)

add_executable(srv main.cpp unp.h unp.cpp)