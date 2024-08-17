cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(clox VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Enable export of compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add debug symbols
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Collect source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Collect header files
file(GLOB_RECURSE HEADER_FILES include/*.hpp include/*.h)

# Add executable target
add_executable(clox ${SRC_FILES} ${HEADER_FILES})

# Set include directories
target_include_directories(clox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
