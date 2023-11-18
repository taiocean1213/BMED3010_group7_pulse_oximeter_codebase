#ifndef FILTERINTERFACE_H
#define FILTERINTERFACE_H

#include "signal_history/SignalHistoryInterface.h"

/**
 * @brief Interface for a filter.
 *
 * This is an abstract base class for a filter. Any concrete filter class should
 * inherit from this class and provide an implementation for the filter method.
 *
 * @tparam element_data_type The data type of the input data elements.
 * @tparam frequency_datatype The data type of the frequency values.
 */
template <typename element_data_type, typename frequency_datatype>
class FilterInterface {
 public:
  virtual ~FilterInterface() {}
  /**
   * @brief Apply the filter to the given data based on the configuration set by
   * the arguments passed to the constructor.
   *
   * @param filterInput The input data to be filtered.
   * @param filterOutput The output data after filtering.
   */
  virtual void process(
      SignalHistoryInterface<element_data_type>* filterInputPtr,
      SignalHistoryInterface<element_data_type>* filterOutputPtr) = 0;
};

#endif
