
/**
 * @interface CalculationModuleInterface
 * @brief Abstract base class for calculation methods.
 */

#ifndef CALCULATORINTERFACE_H
#define CALCULATORINTERFACE_H

#include <vector>

template <class element_type>
class CalculationModuleInterface {
  virtual element_type calculate(std::vector<element_type>&) = 0;
};

#endif