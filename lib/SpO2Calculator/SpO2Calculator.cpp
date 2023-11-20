#include "SpO2Calculator.h"

#include <cmath>    // for std::sqrt
#include <numeric>  // for std::accumulate

#include "signal_history/SignalHistoryInterface.h"

/**
 * @brief Calculate SpO2 from the given signal histories.
 * @param redInfraredSignalPtr Pointer to the signal history for red and
 * infrared signals.
 * @param infraredSignalPtr Pointer to the signal history for infrared signals.
 * @return The calculated SpO2 value.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::calculate(
    SignalHistoryInterface<element_type>* redInfraredSignalPtr,
    SignalHistoryInterface<element_type>* infraredSignalPtr) {
  // Get the data from the signal history objects
  std::vector<element_type> redData;
  std::vector<element_type> infraredData;

  // Populate the redData and infraredData vectors with data from the signal
  // history objects
  for (element_type i = 0; i < redInfraredSignalPtr->size(); i++) {
    redData.push_back(redInfraredSignalPtr->get(i));
    infraredData.push_back(infraredSignalPtr->get(i));
  }

  // Calculate the R value
  element_type RValue = calculateRValue(redData, infraredData);

  // Calculate the SpO2
  element_type result = findSpO2Value(RValue);

  // Reset the history
  redInfraredSignalPtr->reset();
  infraredSignalPtr->reset();

  return result;
};

/**
 * @brief Calculate the R value from the given red and infrared values.
 * @param redValues Vector of red values.
 * @param infraredValues Vector of infrared values.
 * @return The calculated R value.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::calculateRValue(
    std::vector<element_type>& redValues,
    std::vector<element_type>& infraredValues) {
  // Define the literal
  const element_type DEFAULTINITIALVALUE = 0;

  // Calculate the sum of red values
  element_type sumRed =
      std::accumulate(redValues.begin(), redValues.end(), DEFAULTINITIALVALUE);
  // Calculate the sum of infrared values
  element_type sumInfrared = std::accumulate(
      infraredValues.begin(), infraredValues.end(), DEFAULTINITIALVALUE);

  // Calculate the DC component for red and infrared values
  element_type redDC = sumRed / redValues.size();
  element_type infraredDC = sumInfrared / infraredValues.size();

  // Calculate the ACrms for red and infrared values
  element_type redACrms = findACComponentRootMeanSquare(redValues, redDC);
  element_type infraredACrms =
      findACComponentRootMeanSquare(infraredValues, infraredDC);

  // Calculate the R value
  return (redACrms / redDC) / (infraredACrms / infraredDC);
};

/**
 * @brief Calculate the SpO2 from the given R value.
 * @param RValue The R value.
 * @return The calculated SpO2 value.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::findSpO2Value(element_type RValue) {
  // Define the literals
  const element_type R_MIN =
      200;  // Minimum value for RValue (to avoid division by zero)
  const element_type R_MAX = 10000;  // Maximum value for RValue
  const element_type MAX = 100;
  const element_type MIN = 0;
  const element_type FACTOR = 25;
  const element_type ADJUSTMENT = 10;

  element_type SpO2Value;

  // Calculate the SpO2 based on the R value
  if (RValue >= R_MAX) {
    SpO2Value = MAX;
  } else if (RValue <= R_MIN) {
    SpO2Value = MIN;
  } else {
    SpO2Value = MAX + ADJUSTMENT - (FACTOR * RValue);
  }

  return SpO2Value;
};

/**
 * @brief Calculate the root mean square of the AC component from the given
 * values and DC component.
 * @param values Vector of values.
 * @param DCOffset The DC component.
 * @return The calculated root mean square of the AC component.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::findACComponentRootMeanSquare(
    std::vector<element_type>& values, element_type DCOffset) {
  // Define the literal
  const element_type DEFAULTINITIALVALUE = 0;

  // Calculate the AC component by subtracting the DC component from each value
  std::vector<element_type> ACComponent;
  for (element_type value : values) {
    ACComponent.push_back(value - DCOffset);
  }

  // Calculate the sum of the AC component
  float sumAC = std::accumulate(ACComponent.begin(), ACComponent.end(),
                                DEFAULTINITIALVALUE);
  // Calculate the root mean square of the AC component
  element_type acrms = sqrt(sumAC / ACComponent.size());

  return acrms;
};
