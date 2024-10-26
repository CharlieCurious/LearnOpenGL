set(CHAPTER "getting_started/shaders" CACHE STRING "Chapter to compile.")

set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/${CHAPTER}.c")

if (EXISTS ${SOURCE_FILE})
    message(STATUS "Compiling ${CHAPTER} as main executable.")
else()
    message(FATAL_ERROR "The specified source file ${SOURCE_FILE} does not exist.")
endif()

add_executable(main ${SOURCE_FILE})

target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/dependencies/glfw
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include)

target_link_libraries(main glfw glad lib)