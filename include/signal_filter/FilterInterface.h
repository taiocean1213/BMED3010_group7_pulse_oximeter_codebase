#ifndef FILTERINTERFACE_H
#define FILTERINTERFACE_H

#include <vector>

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
  /**
   * @brief Apply the filter to the given data based on the configuration set by
   * the arguments passed to the constructor.
   *
   * @param filterInput The input data to be filtered.
   * @return The filtered output data.
   */
  virtual std::vector<element_data_type> process(
      std::vector<element_data_type> filterInput) = 0;
};

#endif
