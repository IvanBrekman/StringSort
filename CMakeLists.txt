cmake_minimum_required(VERSION 3.20)
project(StringSort C)

set(CMAKE_C_COMPILER g++)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive")

add_executable(StringSort main.c sources/string_funcs.c sources/file_funcs.c sources/test.c sources/standard_str_func.c headers/errorlib.h)
