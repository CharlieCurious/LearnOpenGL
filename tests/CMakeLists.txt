include(CTest)

# Collect test sources.
file(GLOB_RECURSE LIB_TEST_SOURCES "lib/*.c")

# Combine all test sources.
set(TEST_SOURCES ${LIB_TEST_SOURCES})

# The sources to be used in unit tests.
set(SOURCES_TO_LINK lib unity)

# Loop over each test source to create an executable.
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the file name without directory and extension.
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # Add executable for each test.
    add_executable(${TEST_NAME} ${TEST_SOURCE})

    # Link the Unity framework and the
    target_link_libraries(${TEST_NAME} PRIVATE ${SOURCES_TO_LINK})

    # Include directories so the test files can access headers
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

    #Register the test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
