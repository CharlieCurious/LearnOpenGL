add_library(lib STATIC lib.c)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(lib PUBLIC
    ${CMAKE_SOURCE_DIR}/dependencies/glfw/include 
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include)

target_link_libraries(lib PUBLIC glfw glad)