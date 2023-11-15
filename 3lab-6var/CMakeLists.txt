cmake_minimum_required(VERSION 3.23)
project(3lab_6var)

set(CMAKE_CXX_STANDARD 23)

add_executable(3lab_6var main.cpp)

add_custom_command(
        TARGET 3lab_6var PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/files/ $<TARGET_FILE_DIR:3lab_6var>
)