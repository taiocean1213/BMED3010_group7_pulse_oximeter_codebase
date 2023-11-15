
/**
 * @interface SpO2Calculator
 * @brief Abstract base class for calculating SpO2 values.
 */

#ifndef SPO2CALCULATORINTERFACE_H
#define SPO2CALCULATORINTERFACE_H

#include <vector>

#include "CalculationModuleInterface.h"

template <class element_type>
class SpO2CalculatorInterface
    : public CalculationModuleInterface<element_type> {};

#endif