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
   * @param samplingPeriodUs The sampling period in microseconds.
   * @return The calculated SpO2.
   */
  element_type calculate(
      SignalHistoryInterface<element_type>* redIrSignalPtr,
      SignalHistoryInterface<element_type>* infraRedIrSignalPtr,
      element_type samplingPeriodUs) override;

 private:
  /**
   * @brief Calculates the R value from the signal history.
   *
   * @param redInfraredSignalPtr Pointer to the signal history for red and
   * infrared signals.
   * @param infraredSignalPtr Pointer to the signal history for infrared
   * signals.
   * @return The calculated R value.
   */
  element_type calculateRValue(
      SignalHistoryInterface<element_type>* redInfraredSignalPtr,
      SignalHistoryInterface<element_type>* infraredSignalPtr);

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
   * @param ppgSignalHistoryObjectPtr Pointer to the signal history object.
   * @param signalOffset The DC component of the signals.
   * @return The calculated ACrms.
   */
  element_type rootMeanSquare(
      SignalHistoryInterface<element_type>* ppgSignalHistoryObjectPtr,
      element_type signalOffset);
};

// Explicit instantiation
template class SpO2Calculator<double>;

#endif
