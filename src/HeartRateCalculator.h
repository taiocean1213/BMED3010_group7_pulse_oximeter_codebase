#ifndef HEARTRATECALCULATOR_H
#define HEARTRATECALCULATOR_H

#include "biomedical_metrics/HeartRateCalculatorInterface.h"

/**
 * @interface HeartRateCalculator
 * @brief Abstract base class for calculating heart rate values.
 */
template <class element_type>
class HeartRateCalculator : public HeartRateCalculatorInterface<element_type> {
 public:
  /**
   * @brief Calculates the heart rate.
   * @return The calculated heart rate.
   */
  double calculateHeartRate() override;

  /**
   * @brief Processes the heart rate data.
   * @param data The heart rate data.
   */
  void processHeartRateData(element_type data) override;
};

#endif