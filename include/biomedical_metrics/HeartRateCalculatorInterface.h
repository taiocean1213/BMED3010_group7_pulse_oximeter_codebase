
/**
 * @interface HeartRateCalculatorInterface
 * @brief Abstract base class for calculating heart rate values.
 */

#ifndef HEARTRATECALCULATORINTERFACE_H
#define HEARTRATECALCULATORINTERFACE_H

#include <vector>

#include "CalculationModuleInterface.h"

template <class element_type>
class HeartRateCalculatorInterface
    : public CalculationModuleInterface<element_type> {
 public:
  ~HeartRateCalculatorInterface(){};
};

#endif