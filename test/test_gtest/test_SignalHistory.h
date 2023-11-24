#include <gtest/gtest.h>

#include "SignalHistory.h"

// Test case for put method
TEST(SignalHistoryTestCase1, Put) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signal = 1.0;

  // Act
  signalHistory.put(signal);

  // Assert
  EXPECT_EQ(signalHistory.size(), 1);
}

// Test case for get method
TEST(SignalHistoryTestCase2, Get) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signal = 1.0;
  signalHistory.put(signal);

  // Act
  double retrievedSignal = signalHistory.get(0);

  // Assert
  EXPECT_EQ(retrievedSignal, signal);
}

// Test case for min method
TEST(SignalHistoryTestCase3, Min) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signals[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (double signal : signals) {
    signalHistory.put(signal);
  }

  // Act
  double minSignal = signalHistory.min();

  // Assert
  EXPECT_EQ(minSignal, 1.0);
}

// Test case for max method
TEST(SignalHistoryTestCase4, Max) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signals[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (double signal : signals) {
    signalHistory.put(signal);
  }

  // Act
  double maxSignal = signalHistory.max();

  // Assert
  EXPECT_EQ(maxSignal, 5.0);
}

// Test case for size method
TEST(SignalHistoryTestCase5, Size) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signals[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (double signal : signals) {
    signalHistory.put(signal);
  }

  // Act
  double size = signalHistory.size();

  // Assert
  EXPECT_EQ(size, 5);
}

// Test case for reset method
TEST(SignalHistoryTestCase6, Reset) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signals[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (double signal : signals) {
    signalHistory.put(signal);
  }

  // Act
  signalHistory.reset();

  // Assert
  EXPECT_EQ(signalHistory.size(), 0);
}

TEST(SignalHistoryTestCase7, PutWhenFull) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signals[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (double signal : signals) {
    signalHistory.put(signal);
  }

  // Act
  double newSignal = 6.0;
  signalHistory.put(newSignal);

  // Assert
  EXPECT_EQ(signalHistory.size(), 6);
  EXPECT_EQ(signalHistory.get(0), 1.0);
  EXPECT_EQ(signalHistory.get(5), newSignal);
}

TEST(SignalHistoryTestCase8, GetWithInvalidIndex) {
  // Arrange
  SignalHistory<double> signalHistory;
  double signals[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (double signal : signals) {
    signalHistory.put(signal);
  }

  // Act and Assert
  EXPECT_THROW(signalHistory.get(5), std::invalid_argument);
}

TEST(SignalHistoryTestCase9, MinWithEmptyHistory) {
  // Arrange
  SignalHistory<double> signalHistory;

  // Act and Assert
  EXPECT_THROW(signalHistory.min(), std::runtime_error);
}

TEST(SignalHistoryTestCase10, MaxWithEmptyHistory) {
  // Arrange
  SignalHistory<double> signalHistory;

  // Act and Assert
  EXPECT_THROW(signalHistory.max(), std::runtime_error);
}

TEST(SignalHistoryTestCase12, ResetWhenEmpty) {
  // Arrange
  SignalHistory<double> signalHistory;

  // Act
  signalHistory.reset();

  // Assert
  EXPECT_EQ(signalHistory.size(), 0);
}
