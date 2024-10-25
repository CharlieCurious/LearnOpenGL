cmake_minimum_required(VERSION 3.22.1)

project(LearnOpenGL)

set(CMAKE_C_STANDARD 17)
set(ENABLE_TESTING "Compile tests." ON)

if(ENABLE_TESTING)
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g -O0")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Debug, Release)" FORCE)
    add_subdirectory(dependencies/unity)
    add_subdirectory(tests)
    enable_testing()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -03")
    set(CMAKE_BUILD_TYPE "Release"  CACHE STRING "Build type (Debug, Release)" FORCE)
endif()

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(src)
add_subdirectory(lib)
