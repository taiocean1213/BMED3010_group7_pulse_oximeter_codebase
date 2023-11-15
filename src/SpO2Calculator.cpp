/**
 * @file
 * @brief Implementation of the SpO2Calculator class.
 *
 * This file contains the implementation of the SpO2Calculator class.
 */

#include "SpO2Calculator.h"

template <class element_type>
element_type SpO2Calculator<element_type>::calculate(
    std::vector<element_type>& data) {
  /**
   * @brief Calculates the SpO2.
   * @param data A vector of floats representing the SpO2 data.
   * @return The calculated SpO2.
   */
  element_type sum = 0;
  for (element_type value : data) {
    sum += value;
  }
  return sum / data.size();
}
