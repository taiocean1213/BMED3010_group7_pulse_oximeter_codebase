#include <gtest/gtest.h>

#include "FastFourierTransform.h"

class FastFourierTransformTest : public ::testing::Test {
 protected:
  // You can do set-up work for each test here.
  FastFourierTransformTest() {
    // Initialize your FastFourierTransform object here
    transform = new FastFourierTransform<float>();
  }

  // You can do clean-up work that doesn't throw exceptions here.
  ~FastFourierTransformTest() override {
    // Delete your FastFourierTransform object here
    delete transform;
  }

  // Objects declared here can be used by all tests in the test suite for
  // FastFourierTransform. For example: FastFourierTransform<float>* transform;
  FastFourierTransform<float>* transform;
};

// Test case for fastFourierTransform method
TEST_F(FastFourierTransformTest, FastFourierTransformTestCase) {
  // Arrange
  std::vector<float> realInput = {1.0f, 2.0f, 3.0f, 4.0f};
  std::vector<float> imaginaryInput = {0.0f, 0.0f, 0.0f, 0.0f};
  std::vector<float> realOutput;
  std::vector<float> imaginaryOutput;
  std::vector<float> expectedRealOutput = {10.0f, -2.0f, -2.0f, -2.0f};
  std::vector<float> expectedImaginaryOutput = {0.0f, 2.0f, 0.0f, -2.0f};

  // Act
  transform->fastFourierTransform(&realInput, &imaginaryInput, &realOutput,
                                  &imaginaryOutput);

  // Assert
  // Check if the output is as expected here
  EXPECT_EQ(realOutput, expectedRealOutput);
  EXPECT_EQ(imaginaryOutput, expectedImaginaryOutput);
}

TEST_F(FastFourierTransformTest, FFTTestCase) {
  // Arrange
  std::vector<float> realInput = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                  6.0f, 7.0f, 8.0f, 9.0f};
  std::vector<float> imaginaryInput = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 0.0f};
  std::vector<float> realOutput;
  std::vector<float> imaginaryOutput;
  std::vector<float> expectedRealOutput = {45.0f, -4.5f, -4.5f, -4.5f, -4.5f,
                                           -4.5f, -4.5f, -4.5f, -4.5f};
  std::vector<float> expectedImaginaryOutput = {
      0.0f,         12.36364839f, 5.36289117f,  2.59807621f,  0.79347141f,
      -0.79347141f, -2.59807621f, -5.36289117f, -12.36364839f};

  // Act
  transform->fastFourierTransform(&realInput, &imaginaryInput, &realOutput,
                                  &imaginaryOutput);

  // Assert
  EXPECT_EQ(realOutput, expectedRealOutput);
  EXPECT_EQ(imaginaryOutput, expectedImaginaryOutput);
}

// Test case for inverseFastFourierTransform method
TEST_F(FastFourierTransformTest, InverseFastFourierTransformTestCase) {
  // Arrange
  std::vector<float> realInput = {1.0f, 2.0f, 3.0f, 4.0f};
  std::vector<float> imaginaryInput = {0.0f, 0.0f, 0.0f, 0.0f};
  std::vector<float> realOutput;
  std::vector<float> imaginaryOutput;

  // Act
  // transform->inverseFastFourierTransform(&realInput, &imaginaryInput,
  //                                       &realOutput, &imaginaryOutput);

  // Assert
  // Check if the output is as expected here
  // EXPECT_EQ(realOutput, expectedRealOutput);
  // EXPECT_EQ(imaginaryOutput, expectedImaginaryOutput);
}
