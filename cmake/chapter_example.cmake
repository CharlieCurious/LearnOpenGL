function(chapter_example)
    set(EXE example)

    file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(LIB_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")

    set(COMPILER_FLAGS -Wall -g)
    
    # This setup assumes glfw is installed (apt install libglfw3-dev)
    # It also assum glm installed (sudo apt install libglm-dev)
    set(INSTALLED_LIBS glfw)

    add_executable(${EXE} ${SRCS})
    target_include_directories(${EXE} PRIVATE ${INCLUDE} ${LIB_INCLUDE})
    target_compile_options(${EXE} PRIVATE ${COMPILER_FLAGS})
    target_link_libraries(${EXE} PRIVATE ${INSTALLED_LIBS} lib)
endfunction()
