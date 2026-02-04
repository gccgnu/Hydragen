cmake_minimum_required(VERSION 3.10)
project(Hydragen C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "as/*.c")

add_executable(as ${SOURCES})

target_include_directories(hydragen PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/as
)