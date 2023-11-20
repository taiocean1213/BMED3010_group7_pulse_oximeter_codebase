#ifndef HEARTRATECALCULATOR_H
#define HEARTRATECALCULATOR_H

#include <vector>

#include "biomedical_metrics/HeartRateCalculatorInterface.h"
#include "signal_history/SignalHistoryInterface.h"

/**
 * @class HeartRateCalculator
 * @brief This class implements the heart rate calculation logic.
 *
 * This class provides the implementation for the heart rate calculation logic.
 * It inherits from the CalculationModuleInterface class and overrides the
 * calculate function.
 *
 * @tparam element_type The type of the elements in the data vector.
 */
template <class element_type>
class HeartRateCalculator : public HeartRateCalculatorInterface<element_type> {
 public:
  /**
   * @brief Calculates heart rate from red and infrared signal histories.
   * @param redSignalHistoryPtr Pointer to the red signal history.
   * @param infraRedSignalHistoryPtr Pointer to the infrared signal history.
   * @return The calculated heart rate.
   */
  element_type calculate(
      SignalHistoryInterface<element_type>* redSignalHistoryPtr,
      SignalHistoryInterface<element_type>* infraRedSignalHistoryPtr) override;

 private:
  /**
   * @brief Gets the maximum value in the signal history.
   * @param ppgSignalHistoryPtr Pointer to the signal history.
   * @return The maximum value in the signal history.
   */
  element_type getMaxValue(
      SignalHistoryInterface<element_type>* ppgSignalHistoryPtr);

  /**
   * @brief Gets the minimum value in the signal history.
   * @param ppgSignalHistoryPtr Pointer to the signal history.
   * @return The minimum value in the signal history.
   */
  element_type getMinValue(
      SignalHistoryInterface<element_type>* ppgSignalHistoryPtr);

  /**
   * @brief Calculates the threshold for rising edge detection.
   * @param minValue The minimum value in the signal history.
   * @param maxValue The maximum value in the signal history.
   * @param percentage The percentage of the signal history used for threshold
   * calculation.
   * @return The calculated threshold.
   */
  element_type getRisingEdgeThreshold(element_type minValue,
                                      element_type maxValue, double percentage);

  /**
   * @brief Counts the number of rising edges per minute in the signal history.
   * @param ppgSignalHistoryPtr Pointer to the signal history.
   * @param threshold The threshold for rising edge detection.
   * @param samplingPeriodUs The sampling period in microseconds.
   * @return The number of rising edges per minute.
   */
  element_type countRisingEdgesPerMinute(
      SignalHistoryInterface<element_type>* ppgSignalHistoryPtr,
      element_type threshold, element_type samplingPeriodUs);
};
// Explicit instantiation
template class HeartRateCalculator<double>;

#endif
