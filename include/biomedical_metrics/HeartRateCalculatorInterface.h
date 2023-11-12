
/**
 * @interface HeartRateCalculatorInterface
 * @brief Abstract base class for calculating heart rate values.
 */

#ifndef BIOMEDICAL_METRICS_HEARTRATECALCULATORINTERFACE_H
#define BIOMEDICAL_METRICS_HEARTRATECALCULATORINTERFACE_H

#include "../signal_history/SignalHistoryInterface.h"

template <class element_type>
class HeartRateCalculatorInterface
    : public SignalHistoryInterface<element_type> {};

#endif