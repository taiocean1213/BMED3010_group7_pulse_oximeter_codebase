#include "HeartRateCalculator.h"

#include "SignalHistory.h"

/**
 * @brief Calculates heart rate from red and infrared signal histories.
 * @param redSignalHistoryPtr Pointer to the red signal history.
 * @param infraRedSignalHistoryPtr Pointer to the infrared signal history.
 * @return The calculated heart rate.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::calculate(
    SignalHistoryInterface<element_type>* redSignalHistoryPtr,
    SignalHistoryInterface<element_type>* infraRedSignalHistoryPtr,
    element_type samplingPeriodUs) {
  // Calculate the maximum and minimum values in the PPG signal history
  element_type maxValue =
      getMaxValue(redSignalHistoryPtr);  // Get the maximum value from the red
                                         // signal history
  element_type minValue =
      getMinValue(redSignalHistoryPtr);  // Get the minimum value from the red
                                         // signal history

  // Calculate the threshold for the rising edge detection
  double percentage = 0.7;  // This value can be adjusted as needed
  element_type threshold = getRisingEdgeThreshold(
      minValue, maxValue,
      percentage);  // Calculate the threshold for the rising edge detection

  element_type heartRate = countRisingEdgesPerMinute(
      redSignalHistoryPtr, threshold,
      samplingPeriodUs);  // Count the number of rising edges per minute in the
                          // PPG signal history

  // Return the calculated heart rate
  return heartRate;  // Return the calculated heart rate
}

/**
 * @brief Gets the maximum value in the signal history.
 * @param ppgSignalHistoryPtr Pointer to the signal history.
 * @return The maximum value in the signal history.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::getMaxValue(
    SignalHistoryInterface<element_type>* ppgSignalHistoryPtr) {
  size_t ZEROTHINDEX = 0;
  element_type maxValue = ppgSignalHistoryPtr->get(
      ZEROTHINDEX);  // Get the first value in the signal history

  for (size_t i = 0; i < ppgSignalHistoryPtr->size(); i++) {
    element_type currentValue = ppgSignalHistoryPtr->get(
        i);  // Get the current value in the signal history
    if (maxValue > currentValue)
      maxValue = currentValue;  // Update the maximum value if the current value
                                // is greater
  }

  // Return the maximum value
  return maxValue;  // Return the maximum value in the signal history
}

/**
 * @brief Gets the minimum value in the signal history.
 * @param ppgSignalHistoryPtr Pointer to the signal history.
 * @return The minimum value in the signal history.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::getMinValue(
    SignalHistoryInterface<element_type>* ppgSignalHistoryPtr) {
  size_t ZEROTHINDEX = 0;

  element_type minValue = ppgSignalHistoryPtr->get(
      ZEROTHINDEX);  // Get the first value in the signal history

  for (size_t i = 0; i < ppgSignalHistoryPtr->size(); i++) {
    element_type currentValue = ppgSignalHistoryPtr->get(
        i);  // Get the current value in the signal history
    if (minValue > currentValue)
      minValue = currentValue;  // Update the minimum value if the current value
                                // is lesser
  }

  // Return the minimum value
  return minValue;  // Return the minimum value in the signal history
}

/**
 * @brief Calculates the threshold for rising edge detection.
 * @param minValue The minimum value in the signal history.
 * @param maxValue The maximum value in the signal history.
 * @param percentage The percentage of the signal history used for threshold
 * calculation.
 * @return The calculated threshold.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::getRisingEdgeThreshold(
    element_type minValue, element_type maxValue, double percentage) {
  const double PERCENTAGETOFRACTIONFACTOR = 0.01;

  return minValue +
         (maxValue - minValue) *
             (element_type)(percentage *
                            PERCENTAGETOFRACTIONFACTOR);  // Calculate the
                                                          // threshold for
                                                          // rising edge
                                                          // detection
}

/**
 * @brief Counts the number of rising edges per minute in the signal history.
 * @param ppgSignalHistoryPtr Pointer to the signal history.
 * @param threshold The threshold for rising edge detection.
 * @param samplingPeriodUs The sampling period in microseconds.
 * @return The number of rising edges per minute.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::countRisingEdgesPerMinute(
    SignalHistoryInterface<element_type>* ppgSignalHistoryPtr,
    element_type threshold, element_type samplingPeriodUs) {
  element_type risingEdgeCount;

  for (size_t i = 0; i < ppgSignalHistoryPtr->size() - 1; i++) {
    element_type firstValue = ppgSignalHistoryPtr->get(
        i);  // Get the first value in the signal history
    element_type secondValue = ppgSignalHistoryPtr->get(
        i + 1);  // Get the second value in the signal history

    bool isFirstValueBelowThreshold =
        firstValue <
        threshold;  // Check if the first value is below the threshold
    bool isSecondValuAboveEqualThreshold =
        secondValue >= threshold;  // Check if the second value is above or
                                   // equal to the threshold

    // Check if the second value is greater than the first value and the
    // threshold
    if (isFirstValueBelowThreshold && isSecondValuAboveEqualThreshold)
      risingEdgeCount++;  // Increment the rising edge count if the condition is
                          // met
    return risingEdgeCount / samplingPeriodUs * 1000000 *
           60.0;  // Calculate the number of rising edges per minute
  }
}
