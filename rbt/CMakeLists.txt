cmake_minimum_required(VERSION 3.15)
project(red_black_tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(red_black_tree red-black-tree.cpp red-black-tree.h test_rbt.cpp smp.cpp)