cmake_minimum_required(VERSION 3.22.1)

project(LearnOpenGL)

set(CMAKE_C_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Debug, Release)" FORCE)
endif()

# Apply compiler flags based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

if(NOT ENABLE_TESTING)
    set(ENABLE_TESTING "OFF" CACHE STRING "Compile tests" FORCE)
endif()

if(ENABLE_TESTING STREQUAL "ON")
    add_subdirectory(dependencies/external/unity)
    add_subdirectory(tests)
    enable_testing()
endif()

add_subdirectory(dependencies/external/glfw)

add_subdirectory(dependencies/external/cglm)
set(CGLM_SHARED OFF CACHE BOOL "" FORCE)  # Disable shared library
set(CGLM_STATIC ON CACHE BOOL "" FORCE)   # Enable static library

add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/stb_image)
add_subdirectory(src)
add_subdirectory(lib)