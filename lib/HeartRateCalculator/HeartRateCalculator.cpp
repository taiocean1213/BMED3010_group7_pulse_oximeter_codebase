/**
 * @file
 * @brief Implementation of the HeartRateCalculator class.
 *
 * This file contains the implementation of the HeartRateCalculator class.
 */

#include "HeartRateCalculator.h"

/**
 * @brief Calculates the heart rate.
 * @param redIrSignalPtr A vector of floats representing the data collected
 * when the red LED is on.
 * @param infraRedIrSignalPtr A vector of floats representing the data
 * collected when the infraRed LED is on.
 * @return The calculated Heart beat rate.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::calculate(
    SignalHistoryInterface<element_type>* redIrSignalPtr,
    SignalHistoryInterface<element_type>* infraRedIrSignalPtr) {
  element_type sum = 0;
  /*
  for (element_type value : dataPtr) {
    sum += value;
  }
  */
  return sum;
};