// Include the main Google Test header
#include <gtest/gtest.h>

// Include the tested declared functions
#include "../inc/inc.hpp"

/**
 * @brief The Main Testing Function
 *
 * This is the entry point for running all the Google Tests in the project.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int Returns the result of running all tests (0 if all tests passed, non-zero if any failed).
 */
int main(int argc, char **argv) {
  // Initialize Google Test framework
  testing::InitGoogleTest(&argc, argv);

  // Run all the tests and return the result
  return RUN_ALL_TESTS();
}

/**
 * @brief Simple test case that demonstrates basic output
 *
 * This test is used to ensure that a basic output function works as expected.
 */
TEST(TestFn00, Test00) {
  std::cout << "Test True!" << std::endl; // This is just a simple print statement for testing purposes
}
