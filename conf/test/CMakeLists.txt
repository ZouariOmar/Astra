# Set the minimum CMake version
cmake_minimum_required(VERSION 3.29.3)

# Set the project name
project(test)

# Set the CMake C++ version
set(CMAKE_CXX_STANDARD 20)

# Specify the path to your local Google Test installation
set(GTEST_INCLUDE_DIR /usr/include/gtest)
set(GTEST_LIB_DIR /usr/lib)

# Add the test source file(s)
set(SOURCES
  ../../project/tests/test.cpp  # Your test file
)

# Add the executable for the tests
add_executable(${PROJECT_NAME} ${SOURCES})

# Include Google Test headers
include_directories(${GTEST_INCLUDE_DIR})

# Link the Google Test library
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${GTEST_LIB_DIR}/libgtest.so
  ${GTEST_LIB_DIR}/libgtest_main.so
  pthread  # Link with pthread if required
)

# Enable testing
enable_testing()

# Add a test with CTest
add_test(NAME MyTest COMMAND ${PROJECT_NAME})
