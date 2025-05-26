cmake_minimum_required(VERSION 3.30)
project(cw)

set(CMAKE_CXX_STANDARD 26)

add_executable(cw main.cpp
        include/shop.h
        include/department.h
        include/dynamic_list.h
        include/person.h
        include/statick_stack.h
        include/my_const.h)