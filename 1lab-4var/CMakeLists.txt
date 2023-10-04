cmake_minimum_required(VERSION 3.23)
project(1lab_4var)

set(CMAKE_CXX_STANDARD 14)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/testfile.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1lab_4var main.cpp)
