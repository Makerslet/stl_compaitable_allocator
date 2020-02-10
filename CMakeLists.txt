cmake_minimum_required(VERSION 3.5)

project(custom_allocator)

add_executable(allocator main.cpp allocator.h custom_forward_list.h)
set_target_properties(allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
