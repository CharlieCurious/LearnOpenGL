cmake_minimum_required(VERSION 3.22.1)

project(LearnOpenGL)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/unity)
add_subdirectory(src)
add_subdirectory(lib)

add_subdirectory(tests)