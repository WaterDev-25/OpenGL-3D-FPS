# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(OpenGL3DFps)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/thirdparty)
# Add lib directory
link_directories(${CMAKE_SOURCE_DIR}/lib/x64/windows)

# Add game subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/game)
