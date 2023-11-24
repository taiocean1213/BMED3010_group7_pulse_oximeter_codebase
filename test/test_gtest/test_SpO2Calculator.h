#include "SignalHistory.h"
#include "SpO2Calculator.h"
#include "gtest/gtest.h"

TEST(SpO2CalculatorTest1, CalculateTest) {
  // Arrange
  SignalHistory<double>* redSignalHistory = new SignalHistory<double>;
  SignalHistory<double>* infraRedSignalHistory = new SignalHistory<double>;
  SpO2Calculator<double>* SpO2CalculatorObject = new SpO2Calculator<double>;

  double expectedHeartRate = 60;

  for (int i = 0; i < (int)expectedHeartRate; ++i) {
    double time = i / 60.0;
    redSignalHistory->put(sin(2 * M_PI * 1 * time));
    infraRedSignalHistory->put(sin(2 * M_PI * 1 * time));
  }

  // Act
  double samplingPeriodUs = 1e6 / expectedHeartRate;  // Sampling rate of 60 Hz.
  double calculatedHeartRate = SpO2CalculatorObject->calculate(
      redSignalHistory, infraRedSignalHistory, samplingPeriodUs);

  // Assert
  ASSERT_NEAR(expectedHeartRate, calculatedHeartRate,
              1e-6);  // Allow a small margin of error.

  // Clean up.
  delete redSignalHistory;
  delete infraRedSignalHistory;
  delete SpO2CalculatorObject;
}

TEST(SpO2CalculatorTest2, CalculateTest) {
  // Arrange
  SignalHistory<double>* redSignalHistory = new SignalHistory<double>;
  SignalHistory<double>* infraRedSignalHistory = new SignalHistory<double>;
  SpO2Calculator<double>* SpO2CalculatorObject = new SpO2Calculator<double>;

  double expectedHeartRate = 120;

  for (int i = 0; i < (int)expectedHeartRate; ++i) {
    double time = i / 60.0;
    redSignalHistory->put(sin(2 * M_PI * 1 * time));
    infraRedSignalHistory->put(sin(2 * M_PI * 1 * time));
  }

  // Act
  double samplingPeriodUs =
      1e6 / expectedHeartRate;  // Sampling rate of 120 Hz.
  double calculatedHeartRate = SpO2CalculatorObject->calculate(
      redSignalHistory, infraRedSignalHistory, samplingPeriodUs);

  // Assert
  ASSERT_NEAR(expectedHeartRate, calculatedHeartRate,
              1e-6);  // Allow a small margin of error.

  // Clean up.
  delete redSignalHistory;
  delete infraRedSignalHistory;
  delete SpO2CalculatorObject;
}

TEST(SpO2CalculatorTest3, CalculateTest) {
  // Arrange
  SignalHistory<double>* redSignalHistory = new SignalHistory<double>;
  SignalHistory<double>* infraRedSignalHistory = new SignalHistory<double>;
  SpO2Calculator<double>* SpO2CalculatorObject = new SpO2Calculator<double>;

  double expectedHeartRate = 180;

  for (int i = 0; i < (int)expectedHeartRate; ++i) {
    double time = i / 60.0;
    redSignalHistory->put(sin(2 * M_PI * 1 * time));
    infraRedSignalHistory->put(sin(2 * M_PI * 1 * time));
  }

  // Act
  double samplingPeriodUs =
      1e6 / expectedHeartRate;  // Sampling rate of 180 Hz.
  double calculatedHeartRate = SpO2CalculatorObject->calculate(
      redSignalHistory, infraRedSignalHistory, samplingPeriodUs);

  // Assert
  ASSERT_NEAR(expectedHeartRate, calculatedHeartRate,
              1e-6);  // Allow a small margin of error.

  // Clean up.
  delete redSignalHistory;
  delete infraRedSignalHistory;
  delete SpO2CalculatorObject;
}

TEST(SpO2CalculatorTest4, CalculateTest) {
  // Arrange
  SignalHistory<double>* redSignalHistory = new SignalHistory<double>;
  SignalHistory<double>* infraRedSignalHistory = new SignalHistory<double>;
  SpO2Calculator<double>* SpO2CalculatorObject = new SpO2Calculator<double>;

  double expectedHeartRate = 240;

  for (int i = 0; i < (int)expectedHeartRate; ++i) {
    double time = i / 60.0;
    redSignalHistory->put(sin(2 * M_PI * 1 * time));
    infraRedSignalHistory->put(sin(2 * M_PI * 1 * time));
  }

  // Act
  double samplingPeriodUs =
      1e6 / expectedHeartRate;  // Sampling rate of 240 Hz.
  double calculatedHeartRate = SpO2CalculatorObject->calculate(
      redSignalHistory, infraRedSignalHistory, samplingPeriodUs);

  // Assert
  ASSERT_NEAR(expectedHeartRate, calculatedHeartRate,
              1e-6);  // Allow a small margin of error.

  // Clean up.
  delete redSignalHistory;
  delete infraRedSignalHistory;
  delete SpO2CalculatorObject;
}

TEST(SpO2CalculatorTest5, CalculateTest) {
  // Arrange
  SignalHistory<double>* redSignalHistory = new SignalHistory<double>;
  SignalHistory<double>* infraRedSignalHistory = new SignalHistory<double>;
  SpO2Calculator<double>* SpO2CalculatorObject = new SpO2Calculator<double>;

  double expectedHeartRate = 300;

  for (int i = 0; i < (int)expectedHeartRate; ++i) {
    double time = i / 60.0;
    redSignalHistory->put(sin(2 * M_PI * 1 * time));
    infraRedSignalHistory->put(sin(2 * M_PI * 1 * time));
  }

  // Act
  double samplingPeriodUs =
      1e6 / expectedHeartRate;  // Sampling rate of 300 Hz.
  double calculatedHeartRate = SpO2CalculatorObject->calculate(
      redSignalHistory, infraRedSignalHistory, samplingPeriodUs);

  // Assert
  ASSERT_NEAR(expectedHeartRate, calculatedHeartRate,
              1e-6);  // Allow a small margin of error.

  // Clean up.
  delete redSignalHistory;
  delete infraRedSignalHistory;
  delete SpO2CalculatorObject;
}

TEST(SpO2CalculatorTest6, CalculateTest) {
  // Arrange
  SignalHistory<double>* redSignalHistory = new SignalHistory<double>;
  SignalHistory<double>* infraRedSignalHistory = new SignalHistory<double>;
  SpO2Calculator<double>* SpO2CalculatorObject = new SpO2Calculator<double>;

  double expectedHeartRate = 360;

  for (int i = 0; i < (int)expectedHeartRate; ++i) {
    double time = i / 60.0;
    redSignalHistory->put(sin(2 * M_PI * 1 * time));
    infraRedSignalHistory->put(sin(2 * M_PI * 1 * time));
  }

  // Act
  double samplingPeriodUs =
      1e6 / expectedHeartRate;  // Sampling rate of 360 Hz.
  double calculatedHeartRate = SpO2CalculatorObject->calculate(
      redSignalHistory, infraRedSignalHistory, samplingPeriodUs);

  // Assert
  ASSERT_NEAR(expectedHeartRate, calculatedHeartRate,
              1e-6);  // Allow a small margin of error.

  // Clean up.
  delete redSignalHistory;
  delete infraRedSignalHistory;
  delete SpO2CalculatorObject;
}

TEST(SpO2CalculatorTest7, CalculateTest) {
  // Arrange
  SignalHistory<double>* redSignalHistory = new SignalHistory<double>;
  SignalHistory<double>* infraRedSignalHistory = new SignalHistory<double>;
  SpO2Calculator<double>* SpO2CalculatorObject = new SpO2Calculator<double>;

  double expectedHeartRate = 420;

  for (int i = 0; i < (int)expectedHeartRate; ++i) {
    double time = i / 60.0;
    redSignalHistory->put(sin(2 * M_PI * 1 * time));
    infraRedSignalHistory->put(sin(2 * M_PI * 1 * time));
  }

  // Act
  double samplingPeriodUs =
      1e6 / expectedHeartRate;  // Sampling rate of 420 Hz.
  double calculatedHeartRate = SpO2CalculatorObject->calculate(
      redSignalHistory, infraRedSignalHistory, samplingPeriodUs);

  // Assert
  ASSERT_NEAR(expectedHeartRate, calculatedHeartRate,
              1e-6);  // Allow a small margin of error.

  // Clean up.
  delete redSignalHistory;
  delete infraRedSignalHistory;
  delete SpO2CalculatorObject;
}
