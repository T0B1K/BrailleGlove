cmake_minimum_required(VERSION 3.14)
project(MyProject)

# Enable testing
enable_testing()

# Add source files
add_executable(MyExecutable src/main.cpp)

# Add test files
add_executable(MyTests test/test_main.cpp)

# Find GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Link GoogleTest to test executable
target_link_libraries(MyTests gtest_main)

# Register tests
add_test(NAME MyTests COMMAND MyTests)
