cmake_minimum_required(VERSION 3.22.1)

project(LearnOpenGL LANGUAGES C CXX VERSION 1.0)

set(CMAKE_CXX_COMPILER "g++-12" CACHE STRING "C++ compiler to use")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(chapter_example)
include(libs)

add_subdirectory(learn_opengl)
