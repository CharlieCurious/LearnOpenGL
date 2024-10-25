add_library(lib STATIC lib.c)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})