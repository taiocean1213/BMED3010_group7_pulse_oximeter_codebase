#include <unity.h>

#define ISPPGCODETEST 1

#include "FastFourierTransform.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_fastFourierTransform(void) {
  FastFourierTransform<float> fft;
  std::vector<float> realInput = {1.0, 2.0, 3.0, 4.0};
  std::vector<float> imaginaryInput = {0.0, 0.0, 0.0, 0.0};
  float sampleSize = 4;

  std::vector<float> result =
      fft.fastFourierTransform(realInput, imaginaryInput, sampleSize);

  TEST_ASSERT_EQUAL_FLOAT(10.0, result[0]);  // Expected result
}

void test_inverseFastFourierTransform(void) {
  FastFourierTransform<float> fft;
  std::vector<float> realInput = {1.0, 2.0, 3.0, 4.0};
  std::vector<float> imaginaryInput = {0.0, 0.0, 0.0, 0.0};
  float sampleSize = 4;

  std::vector<float> result =
      fft.inverseFastFourierTransform(realInput, imaginaryInput, sampleSize);

  // Add your assertion here
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_fastFourierTransform);
  RUN_TEST(test_inverseFastFourierTransform);
  return UNITY_END();
}
