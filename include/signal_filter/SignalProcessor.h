
/**
 * @interface SignalProcessor
 * @brief Abstract base class for signal processing.
 * @
 */

#ifndef SIGNAL_FILTER_SIGNALPROCESSOR_H
#define SIGNAL_FILTER_SIGNALPROCESSOR_H

#include "../signal_history/SignalHistoryInterface.h"

template <class element_type>
class SignalProcessor : public SignalHistoryInterface<element_type> {};

#endif