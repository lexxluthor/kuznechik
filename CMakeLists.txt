cmake_minimum_required(VERSION 3.22)
project(Kuznechik)

set(CMAKE_CXX_STANDARD 14)

add_executable(Kuznechik byte_block.h byte_block.cpp kuznechik.h kuznechik.cpp test_kuznechik.cpp)
