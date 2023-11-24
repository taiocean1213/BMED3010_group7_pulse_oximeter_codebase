#include "HeartRateCalculator.h"

#include "SignalHistory.h"

/**
 * @brief Class instance destructor.
 */
template <class element_type>
HeartRateCalculator<element_type>::~HeartRateCalculator() {}

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
  element_type maxValue = getMaxValue(redSignalHistoryPtr);
  element_type minValue = getMinValue(redSignalHistoryPtr);

  // Calculate the threshold for the rising edge detection
  double percentage = 0.9;
  element_type threshold =
      getRisingEdgeThreshold(minValue, maxValue, percentage);

  // Count the number of rising edges per minute in the PPG signal history
  element_type heartRate = countRisingEdgesPerMinute(
      redSignalHistoryPtr, threshold, samplingPeriodUs);

  // Return the calculated heart rate
  return heartRate;
}

/**
 * @brief Gets the maximum value in the signal history.
 * @param ppgSignalHistoryPtr Pointer to the signal history.
 * @return The maximum value in the signal history.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::getMaxValue(
    SignalHistoryInterface<element_type>* ppgSignalHistoryPtr) {
  // Return the maximum value in the signal history
  return ppgSignalHistoryPtr->max();
}

/**
 * @brief Gets the minimum value in the signal history.
 * @param ppgSignalHistoryPtr Pointer to the signal history.
 * @return The minimum value in the signal history.
 */
template <class element_type>
element_type HeartRateCalculator<element_type>::getMinValue(
    SignalHistoryInterface<element_type>* ppgSignalHistoryPtr) {
  // Return the maximum value in the signal history
  return ppgSignalHistoryPtr->min();
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
  // Calculate the threshold for rising edge detection
  return minValue + (maxValue - minValue) *
                        (element_type)(percentage * PERCENTAGETOFRACTIONFACTOR);
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
  element_type risingEdgeCount = 0;

  // Calculate the timeframe in seconds
  double timeFrameSec = static_cast<double>(ppgSignalHistoryPtr->size()) *
                        static_cast<double>(samplingPeriodUs) / 1e6;

  // Calculate the timeframe in minutes
  double timeFrameMin = timeFrameSec / 60.0;

  for (unsigned int i = 0; i < ppgSignalHistoryPtr->size() - 1; i++) {
    // Get the first value in the signal history
    element_type firstValue = ppgSignalHistoryPtr->get(i);
    // Get the second value in the signal history
    element_type secondValue = ppgSignalHistoryPtr->get(i + 1);

    bool isFirstValueBelowThreshold =
        firstValue <
        threshold;  // Check if the first value is below the threshold
    bool isSecondValuAboveEqualThreshold =
        secondValue >= threshold;  // Check if the second value is above or
                                   // equal to the threshold

    // Check if the second value is greater than the first value and the
    // threshold, then count it
    if (isFirstValueBelowThreshold && isSecondValuAboveEqualThreshold)
      risingEdgeCount++;
  }

  // Calculate the heart rate by dividing the number of rising edges by the
  // timeframe in minutes
  return static_cast<element_type>(static_cast<double>(risingEdgeCount) /
                                   timeFrameMin);
}
