# 3.9 adds support for "GoogleTest" which enumerates the tests inside
# of the code and adds them to ctest.
# Default cmake is 3.5.1 on ubuntu 16.04
cmake_minimum_required(VERSION 3.5)

project(wordfreq)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

include(CTest)

add_subdirectory(src)
add_subdirectory(test)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "wordfreq")
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)