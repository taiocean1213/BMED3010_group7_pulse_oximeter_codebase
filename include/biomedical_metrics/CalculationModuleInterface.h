
/**
 * @interface CalculationModuleInterface
 * @brief Abstract base class for calculation methods.
 */

#ifndef CALCULATORINTERFACE_H
#define CALCULATORINTERFACE_H

#include <vector>

#include "signal_history/SignalHistoryInterface.h"

template <class element_type>
class CalculationModuleInterface {
  virtual element_type calculate(SignalHistoryInterface<element_type>*) = 0;
};

#endif