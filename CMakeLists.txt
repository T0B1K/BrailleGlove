# Add GoogleTest subdirectory
add_subdirectory(googletest)

# Enable testing
enable_testing()

# Add your test executable
add_executable(runTests test/test_main.cpp)

# Link GoogleTest and pthread
target_link_libraries(runTests gtest gtest_main pthread)

# Add a test
add_test(NAME MyTest COMMAND runTests)
