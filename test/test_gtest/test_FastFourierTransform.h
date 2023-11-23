#include <gtest/gtest.h>

#include "FastFourierTransform.h"

// Test case for fastFourierTransform method
TEST(FastFourierTransformTestCase1, FastFourierTransform) {
  // Arrange
  std::vector<double> realInput = {0.0d, 1.0d, 3.0d, 4.0d,
                                   4.0d, 3.0d, 1.0d, 0.0d};
  std::vector<double> imaginaryInput = {0.0d, 1.0d, 3.0d, 4.0d,
                                        4.0d, 3.0d, 1.0d, 0.0d};
  std::vector<double> realOutput;
  std::vector<double> imaginaryOutput;
  std::vector<double> expectedRealOutput = {
      16.0d, -4.82842712d, 0.0d, -0.343146d, 0.0d, 0.828427d, 0.0d, -11.6569d};
  std::vector<double> expectedImaginaryOutput = {
      16.0d, -11.6569d, 0.0d, 0.828427d, 0.0d, -0.343146d, 0.0d, -4.82843d};

  // Act
  FastFourierTransform<double>* transform = new FastFourierTransform<double>();
  transform->fastFourierTransform(&realInput, &imaginaryInput, &realOutput,
                                  &imaginaryOutput);
  delete transform;

  // Assert
  EXPECT_EQ(realOutput.size(), expectedRealOutput.size());
  EXPECT_EQ(imaginaryOutput.size(), expectedImaginaryOutput.size());
  try {
    for (unsigned int i = 0; i < realOutput.size(); i++) {
      double abs_error = 0.001;
      EXPECT_NEAR(realOutput[i], expectedRealOutput[i], abs_error);
      EXPECT_NEAR(imaginaryOutput[i], expectedImaginaryOutput[i], abs_error);
    }
  } catch (...) {
    EXPECT_EQ(realOutput, expectedRealOutput);
    EXPECT_EQ(imaginaryOutput, expectedImaginaryOutput);
  }
}

// Test case for fastFourierTransform method
TEST(FastFourierTransformTestCase2, FastFourierTransform) {
  // Arrange
  std::vector<float> realInput = {1.0f, 2.0f, 3.0f, 4.0f};
  std::vector<float> imaginaryInput = {0.0f, 0.0f, 0.0f, 0.0f};
  std::vector<float> realOutput;
  std::vector<float> imaginaryOutput;
  std::vector<float> expectedRealOutput = {10.0f, -2.0f, -2.0f, -2.0f};
  std::vector<float> expectedImaginaryOutput = {0.0f, 2.0f, 0.0f, -2.0f};

  // Act
  FastFourierTransform<float>* transform = new FastFourierTransform<float>();
  transform->fastFourierTransform(&realInput, &imaginaryInput, &realOutput,
                                  &imaginaryOutput);
  delete transform;

  // Assert
  EXPECT_EQ(realOutput.size(), expectedRealOutput.size());
  EXPECT_EQ(imaginaryOutput.size(), expectedImaginaryOutput.size());
  for (unsigned int i = 0; i < realOutput.size(); i++) {
    double abs_error = 0.001;
    EXPECT_NEAR(realOutput[i], expectedRealOutput[i], abs_error);
    EXPECT_NEAR(imaginaryOutput[i], expectedImaginaryOutput[i], abs_error);
  }
}
TEST(FastFourierTransformTestCase3, FastFourierTransform) {
  // Arrange
  std::vector<float> realInput = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                  6.0f, 7.0f, 8.0f, 9.0f};
  std::vector<float> imaginaryInput = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 0.0f};
  std::vector<float> realOutput;
  std::vector<float> imaginaryOutput;
  std::vector<float> expectedRealOutput = {
      45.0f, -17.13707118f, 5.0f, -5.6199144f,  5.0f, -4.72323135f,
      5.0f,  -4.51978306f,  5.0f, -4.51978306f, 5.0f, -4.72323135f,
      5.0f,  -5.6199144f,   5.0f, -17.13707118f};
  std::vector<float> expectedImaginaryOutput = {
      0.0f,  -25.13669746f, 9.65685425f,  -7.48302881f,
      4.0f,  -3.34089319f,  1.65685425f,  -0.99456184f,
      0.0f,  0.99456184f,   -1.65685425f, 3.34089319f,
      -4.0f, 7.48302881f,   -9.65685425f, 25.13669746f};

  // Act
  FastFourierTransform<float>* transform = new FastFourierTransform<float>();
  transform->fastFourierTransform(&realInput, &imaginaryInput, &realOutput,
                                  &imaginaryOutput);
  delete transform;

  // Assert
  EXPECT_EQ(realOutput.size(), expectedRealOutput.size());
  EXPECT_EQ(imaginaryOutput.size(), expectedImaginaryOutput.size());
  try {
    for (unsigned int i = 0; i < realOutput.size(); i++) {
      double abs_error = 0.001;
      EXPECT_NEAR(realOutput[i], expectedRealOutput[i], abs_error);
      EXPECT_NEAR(imaginaryOutput[i], expectedImaginaryOutput[i], abs_error);
    }
  } catch (...) {
    EXPECT_EQ(realOutput, expectedRealOutput);
    EXPECT_EQ(imaginaryOutput, expectedImaginaryOutput);
  }
}
