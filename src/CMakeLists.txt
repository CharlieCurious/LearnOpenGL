add_executable(main main.c)

target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/dependencies/glfw
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include)

target_link_libraries(main glfw glad)