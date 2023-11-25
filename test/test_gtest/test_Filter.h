#include <gtest/gtest.h>

#include <cmath>

#include "FastFourierTransform.h"
#include "Filter.h"
#include "SignalHistory.h"

class FilterTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize the filter with test data
    filter = new Filter<double, double>(passbands, stopbands, samplingPeriodUs,
                                        &fft);
  }

  void TearDown() override {
    // Clean up the filter after each test
    delete filter;
  }

  Filter<double, double>* filter;
  std::vector<std::pair<double, double>> passbands = {{0, 1}, {2, 3}};
  std::vector<std::pair<double, double>> stopbands = {{1, 2}};
  double samplingPeriodUs = 0.01;
  FastFourierTransform<double> fft;
};

TEST_F(FilterTest, ProcessTest) {
  // Create a test input signal
  SignalHistory<double>* input = new SignalHistory<double>();
  for (int i = 0; i < 10; ++i) {
    input->put(i);
  }

  // Create a test output signal
  SignalHistory<double>* output = new SignalHistory<double>();

  // Apply the filter to the input signal
  filter->process(input, output);

  // Check the output signal
  ASSERT_EQ(output->size(), 16);
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(output->get(i), i, 0.1);
  }

  // Clean up the test signals
  delete input;
  delete output;
}

TEST_F(FilterTest, ProcessTestPassband) {
  // Create a test input signal
  SignalHistory<double>* input = new SignalHistory<double>();
  for (int i = 0; i < 10; ++i) {
    input->put(i * 0.1);  // Frequency in passband
  }

  // Create a test output signal
  SignalHistory<double>* output = new SignalHistory<double>();

  // Apply the filter to the input signal
  filter->process(input, output);

  // Check the output signal
  ASSERT_EQ(output->size(), 16);
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(output->get(i), i * 0.1, 0.01);
  }

  // Clean up the test signals
  delete input;
  delete output;
}

TEST_F(FilterTest, ProcessTestStopband) {
  // Create a test input signal
  SignalHistory<double>* input = new SignalHistory<double>();
  for (double timeSeconds = 0; timeSeconds < 0.4; timeSeconds += 0.01) {
    input->put(std::sin(2 * M_PI * 1.5 * timeSeconds));
  }

  // Create a test output signal
  SignalHistory<double>* output = new SignalHistory<double>();

  // Apply the filter to the input signal
  filter->process(input, output);

  // Check the output signal
  ASSERT_EQ(output->size(), 48);
  for (int i = 0; i < 40; ++i) {
    EXPECT_NEAR(output->get(i), 0, 0.1);
  }

  // Clean up the test signals
  delete input;
  delete output;
}

TEST_F(FilterTest, ProcessTestMixed) {
  // Create a test input signal
  SignalHistory<double>* input = new SignalHistory<double>();
  for (int i = 0; i < 10; ++i) {
    input->put(i * 0.1 + 1.5);  // Frequency in both passband and stopband
  }

  // Create a test output signal
  SignalHistory<double>* output = new SignalHistory<double>();

  // Apply the filter to the input signal
  filter->process(input, output);

  // Check the output signal
  ASSERT_EQ(output->size(), 16);
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(output->get(i), 0, 0.1);
  }

  // Clean up the test signals
  delete input;
  delete output;
}
