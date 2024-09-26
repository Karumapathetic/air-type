cmake_minimum_required(VERSION 3.27)
project("R-Type Graphics Lib")

add_library(
    Graphics STATIC
    tmp.cpp
)

target_include_directories(
    Graphics PUBLIC
    "include"
)
