function(libs)
    file(GLOB_RECURSE SRCS 
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" 
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

    set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

    add_library(lib ${SRCS})
    target_include_directories(lib PUBLIC ${INCLUDE})
endfunction()
