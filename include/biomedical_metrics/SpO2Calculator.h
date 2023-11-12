
/**
 * @interface SpO2Calculator
 * @brief Abstract base class for calculating SpO2 values.
 */

#ifndef BIOMEDICAL_METRICS_SPO2CALCULATOR_H
#define BIOMEDICAL_METRICS_SPO2CALCULATOR_H

#include "../signal_history/SignalHistoryInterface.h"

template <class element_type>
class HeartRateCalculator : public SignalHistoryInterface<element_type> {};

#endif