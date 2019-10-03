cmake_minimum_required(VERSION 3.15)
project(TheHashRacer)

set(CMAKE_CXX_STANDARD 17)

add_executable(TheHashRacer Sources/main.cpp Hash.cpp Headers/Hash.h)