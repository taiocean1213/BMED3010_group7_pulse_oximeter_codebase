#include <gtest/gtest.h>

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
  std::vector<std::pair<double, double>> stopbands = {{1.5, 2.5}};
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
  ASSERT_EQ(output->size(), 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(output->get(i), i);
  }

  // Clean up the test signals
  delete input;
  delete output;
}
