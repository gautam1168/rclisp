cmake_minimum_required (VERSION 2.6)
project (rclisp)

set(HOME /Users/gauravgautam)

include_directories(${CMAKE_SOURCE_DIR}/headers
                    ${HOME}/Public/cmocka-1.1.0/include)

link_directories(${HOME}/Public/cmocka-1.1.0/build/src)

set(CMAKE_C_FLAGS "-std=c99")

add_subdirectory (src)
add_subdirectory(test)
