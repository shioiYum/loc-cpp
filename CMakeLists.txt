cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(clox VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(clox ${SRC_FILES})

target_include_directories(clox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)