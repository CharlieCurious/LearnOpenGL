set(CHAPTER "getting_started" CACHE STRING "Chapter to compile.")
set(LESSON "shaders" CACHE STRING "Lesson to compile.")

set(SHADERS_SRC_FOLDER "${CMAKE_SOURCE_DIR}/src/${CHAPTER}/shaders")
set(SHADERS_BUILD_FOLDER "${CMAKE_BINARY_DIR}/src/shaders")

# Copy shaders at build time
file(GLOB SHADER_FILES "${SHADERS_SRC_FOLDER}/*") # Needed to track changes on the shader files.
add_custom_command(
    OUTPUT "${SHADERS_BUILD_FOLDER}" 
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SHADERS_SRC_FOLDER}" "${SHADERS_BUILD_FOLDER}" 
    DEPENDS "${SHADER_FILES}"
)

set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/${CHAPTER}/${LESSON}.c")

if (EXISTS ${SOURCE_FILE})
    message(STATUS "Compiling ${CHAPTER}/${LESSON}.c as main executable.")
else()
    message(FATAL_ERROR "The specified source file ${SOURCE_FILE} does not exist.")
endif()

add_executable(main ${SOURCE_FILE})
add_custom_target(copy_shaders ALL DEPENDS "${SHADERS_BUILD_FOLDER}")

target_link_libraries(main glfw glad lib)