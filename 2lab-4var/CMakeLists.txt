cmake_minimum_required(VERSION 3.23)
project(2lab_4var)

set(CMAKE_CXX_STANDARD 23)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/files DESTINATION ${CMAKE_CURRENT_BINARY_DIR} FILES_MATCHING PATTERN "*.txt")

add_executable(2lab_4var main.cpp)
