/**
 * @file
 * @brief Implementation of the HeartRateCalculator class.
 *
 * This file contains the implementation of the HeartRateCalculator class.
 */

#include "HeartRateCalculator.h"

template <class element_type>
element_type HeartRateCalculator<element_type>::calculate(
    std::vector<element_type>& data) {
  /**
   * @brief Calculates the heart rate.
   * @param data A vector of integers representing the heart rate data.
   * @return The calculated heart rate.
   */
  element_type sum = 0;
  for (element_type value : data) {
    sum += value;
  }
  return sum;
}
