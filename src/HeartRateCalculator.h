#ifndef HEARTRATECALCULATOR_H
#define HEARTRATECALCULATOR_H

#include "biomedical_metrics/HeartRateCalculatorInterface.h"

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
   * @brief Calculates the heart rate.
   * @param data A vector of integers representing the heart rate data.
   * @return The calculated heart rate.
   */
  element_type calculate(
      SignalHistoryInterface<element_type>* dataPtr) override;
};

#endif