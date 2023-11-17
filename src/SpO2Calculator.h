#ifndef SPO2CALCULATOR_H
#define SPO2CALCULATOR_H

#include "biomedical_metrics/SpO2CalculatorInterface.h"

/**
 * @class SpO2Calculator
 * @brief This class implements the SpO2 calculation logic.
 *
 * This class provides the implementation for the SpO2 calculation logic.
 * It inherits from the CalculationModuleInterface class and overrides the
 * calculate function.
 *
 * @tparam element_type The type of the elements in the data vector.
 */
template <class element_type>
class SpO2Calculator : public SpO2CalculatorInterface<element_type> {
 public:
  /**
   * @brief Calculates the SpO2.
   * @param data A vector of floats representing the SpO2 data.
   * @return The calculated SpO2.
   */
  element_type calculate(
      SignalHistoryInterface<element_type>* dataPtr) override;
};

#endif