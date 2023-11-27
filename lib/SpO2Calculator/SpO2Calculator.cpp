#include "SpO2Calculator.h"

#ifdef UNIT_TEST
#include <stdexcept>

#endif

#include <cmath>    // for std::sqrt
#include <numeric>  // for std::accumulate

#include "signal_history/SignalHistoryInterface.h"

/**
 * @brief Class instance destructor.
 */
template <class element_type>
SpO2Calculator<element_type>::~SpO2Calculator() {}
/**
 * @brief Calculate SpO2 from the given signal histories.
 * @param redInfraredSignalPtr Pointer to the signal history for red and
 * infrared signals.
 * @param infraredSignalPtr Pointer to the signal history for infrared signals.
 * @param samplingPeriodUs The sampling period in microseconds.
 * @return The calculated SpO2 value.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::calculate(
    SignalHistoryInterface<element_type>* redInfraredSignalPtr,
    SignalHistoryInterface<element_type>* infraredSignalPtr,
    element_type samplingPeriodUs) {
  // Calculate the R value
  element_type RValue =
      calculateRValue(redInfraredSignalPtr, infraredSignalPtr);

  // Calculate the SpO2
  element_type result = findSpO2Value(RValue);

  return result;
};

/**
 * @brief Calculate the R value from the given red and infrared values.
 * @param redInfraredSignalPtr Pointer to the signal history for red and
 * infrared signals.
 * @param infraredSignalPtr Pointer to the signal history for infrared signals.
 * @return The calculated R value.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::calculateRValue(
    SignalHistoryInterface<element_type>* redInfraredSignalPtr,
    SignalHistoryInterface<element_type>* infraredSignalPtr) {
#ifdef UNIT_TEST

  // Check if the pointers are not null
  if (!redInfraredSignalPtr || !infraredSignalPtr) {
    throw std::invalid_argument("Pointers cannot be null");
  }
#endif

  // Define the literal
  const element_type DEFAULTINITIALVALUE = 0;

  // declare the variables
  element_type sumOfRedSignals = DEFAULTINITIALVALUE;
  element_type sumOfInfraRedSignals = DEFAULTINITIALVALUE;

#ifdef UNIT_TEST
  // Check if the size of the objects is not zero before accessing their
  // elements
  if (redInfraredSignalPtr->size() == 0 || infraredSignalPtr->size() == 0) {
    throw std::invalid_argument("Size of the objects cannot be zero");
  }
#endif

  // Populate the redData and infraredData vectors with data from the signal
  // history objects
  for (element_type i = 0; i < redInfraredSignalPtr->size(); i++) {
    sumOfRedSignals += redInfraredSignalPtr->get(i);
    sumOfInfraRedSignals += infraredSignalPtr->get(i);
  }

  // Calculate the DC component for red and infrared values
  element_type redSignalAverage =
      sumOfRedSignals / redInfraredSignalPtr->size();
  element_type rinfraRedSignalAverage =
      sumOfInfraRedSignals / infraredSignalPtr->size();

  // Calculate the ACrms for red and infrared values
  element_type redACrms =
      rootMeanSquare(redInfraredSignalPtr, redSignalAverage);
  element_type infraredACrms =
      rootMeanSquare(infraredSignalPtr, rinfraRedSignalAverage);

  // Calculate the R value
  return (redACrms / redSignalAverage) /
         (infraredACrms / rinfraRedSignalAverage);
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
 * @param ppgSignalHistoryObjectPtr Pointer to the signal history object.
 * @param signalOffset The DC component of the signal.
 * @return The calculated root mean square of the AC component.
 */
template <class element_type>
element_type SpO2Calculator<element_type>::rootMeanSquare(
    SignalHistoryInterface<element_type>* ppgSignalHistoryObjectPtr,
    element_type signalOffset) {
  // Define the literal
  const element_type DEFAULTINITIALVALUE = 0;

  element_type sum = DEFAULTINITIALVALUE;
  element_type elementCountInHistoryObjectPtr =
      ppgSignalHistoryObjectPtr->size();

  for (size_t i = DEFAULTINITIALVALUE; i < elementCountInHistoryObjectPtr;
       i++) {
    element_type offsetted_element =
        ppgSignalHistoryObjectPtr->get(i) - signalOffset;
    sum += offsetted_element * offsetted_element;
  }

  return std::sqrt(sum / elementCountInHistoryObjectPtr);
};
