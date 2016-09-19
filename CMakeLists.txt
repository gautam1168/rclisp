cmake_minimum_required (VERSION 2.6)
project (rclisp)

include_directories(${CMAKE_SOURCE_DIR}/headers)
set(CMAKE_C_FLAGS "-std=c99")

add_subdirectory (src)
