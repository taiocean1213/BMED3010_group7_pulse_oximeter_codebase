#include <gtest/gtest.h>

#include "test_gtest/test_FastFourierTransform.h"
#include "test_gtest/test_Filter.h"
#include "test_gtest/test_HeartRateCalculator.h"
#include "test_gtest/test_SignalHistory.h"
#include "test_gtest/test_SpO2Calculator.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // if you plan to use GMock, replace the line above with
  // ::testing::InitGoogleMock(&argc, argv);

  if (RUN_ALL_TESTS())
    ;

  // Always return zero-code and allow PlatformIO to parse results
  return 0;
}