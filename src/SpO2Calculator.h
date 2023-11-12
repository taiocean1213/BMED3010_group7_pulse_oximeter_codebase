#ifndef SPO2CALCULATOR_H
#define SPO2CALCULATOR_H

#include "signal_history/SignalHistoryInterface.h"
#include <Arduino.h>

/**
 * @interface SpO2Calculator
 * @brief Abstract base class for calculating SpO2 values.
 */
template <class element_type>
class SpO2Calculator : public SignalHistoryInterface<element_type> {
public:
  /**
   * @brief Calculates the SpO2 value.
   * @return The calculated SpO2 value.
   */
  double calculateSpO2() override;

  /**
   * @brief Processes the SpO2 data.
   * @param data The SpO2 data.
   */
  void processSpO2Data(element_type data) override;
};

#endif