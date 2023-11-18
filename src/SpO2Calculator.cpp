/**
 * @file
 * @brief Implementation of the SpO2Calculator class.
 *
 * This file contains the implementation of the SpO2Calculator class.
 */

#include "SpO2Calculator.h"

/**
 * @brief Calculates the SpO2.
 * @param redIrSignalPtr A vector of floats representing the data collected when
 * the red LED is on.
 * @param infraRedIrSignalPtr A vector of floats representing the data collected
 * when the infraRed LED is on.
 * @return The calculated SpO2.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::calculate(
    SignalHistoryInterface<element_type>* redIrSignalPtr,
    SignalHistoryInterface<element_type>* infraRedIrSignalPtr) {
  element_type sum = 0;
  /*
  for (element_type value : data) {
    sum += value;
  }
  return sum / data.size();
  */
  return sum;
};