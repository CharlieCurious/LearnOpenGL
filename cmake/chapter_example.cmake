function(chapter_example)
    set(EXE example)

    file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(LIB_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")

    set(COMPILER_FLAGS -Wall -g)

    # This setup assumes glfw is installed (apt install libglfw3-dev)
    # It also assum glm installed (sudo apt install libglm-dev)
    set(INSTALLED_LIBS glfw)

    # Add Assimp lib path
    set(ASSIMP_LIB_DIR ${CMAKE_SOURCE_DIR}/external/assimp/build/bin)
    set(ASSIMP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/assimp/build/include)

    add_executable(${EXE} ${SRCS})
    target_include_directories(${EXE} PRIVATE ${INCLUDE} ${LIB_INCLUDE} ${ASSIMP_INCLUDE_DIR})
    target_compile_options(${EXE} PRIVATE ${COMPILER_FLAGS})
    target_link_libraries(${EXE} PRIVATE ${INSTALLED_LIBS} lib assimp)
    target_link_options(${EXE} PRIVATE -Wl,-rpath,${ASSIMP_LIB_DIR})

    # Ensure runtime linker can find libassimp.so at runtime
    set(CMAKE_INSTALL_RPATH ${ASSIMP_LIB_DIR})
endfunction()
