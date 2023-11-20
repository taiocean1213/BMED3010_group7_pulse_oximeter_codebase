#ifndef SPO2CALCULATOR_H
#define SPO2CALCULATOR_H

#include "biomedical_metrics/SpO2CalculatorInterface.h"
#include "signal_history/SignalHistoryInterface.h"

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
   * @param redIrSignalPtr A vector of floats representing the data collected
   * when the red LED is on.
   * @param infraRedIrSignalPtr A vector of floats representing the data
   * collected when the infraRed LED is on.
   * @return The calculated SpO2.
   */
  element_type calculate(
      SignalHistoryInterface<element_type>* redIrSignalPtr,
      SignalHistoryInterface<element_type>* infraRedIrSignalPtr) override;

 private:
  /**
   * @brief Calculates the R value from the signal history.
   *
   * @param redValues The red signal values.
   * @param irValues The infrared signal values.
   * @return The calculated R value.
   */
  element_type calculateRValue(std::vector<element_type>& redValues,
                               std::vector<element_type>& irValues);

  /**
   * @brief Calculates the SpO2 from the R value.
   *
   * @param RValue The R value.
   * @return The calculated SpO2.
   */
  element_type findSpO2Value(element_type RValue);

  /**
   * @brief Calculates the root mean square of the AC component of the signals.
   *
   * @param values The signal values.
   * @param dc The DC component of the signals.
   * @return The calculated ACrms.
   */
  element_type findACComponentRootMeanSquare(std::vector<element_type>& values,
                                             element_type DCOffset);
};

// Explicit instantiation
template class SpO2Calculator<double>;

#endif
