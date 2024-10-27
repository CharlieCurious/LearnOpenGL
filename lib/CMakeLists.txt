file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_library(lib STATIC ${SOURCE_FILES})

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(lib PUBLIC
    ${CMAKE_SOURCE_DIR}/dependencies/glfw/include 
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(lib PUBLIC glfw glad)