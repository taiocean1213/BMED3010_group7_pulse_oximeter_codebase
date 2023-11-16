#ifndef FILTER_H
#define FILTER_H

#include "signal_filter/FastFourierTransformInterface.h"
#include "signal_filter/FilterInterface.h"

/**
 * @brief Implementation of a filter using the Fast Fourier Transform.
 *
 * This class represents a filter that uses the Fast Fourier Transform (FFT)
 * algorithm to process and filter input data based on the provided passbands
 * and stopbands.
 *
 * @tparam element_data_type The data type of the input data elements.
 * @tparam frequency_datatype The data type of the frequency values.
 */
template <typename element_data_type, typename frequency_datatype>
class Filter : public FilterInterface<element_data_type, frequency_datatype> {
 public:
  /**
   * @brief Constructor of the Filter class.
   *
   * This constructor initializes the filter with the provided passbands,
   * stopbands, sampling frequency, and FFT instance.
   *
   * @param passbands The vector of pairs representing the passbands.
   * @param stopbands The vector of pairs representing the stopbands.
   * @param samplingFrequency The sampling frequency of the signal.
   * @param fft The instance of the FastFourierTransformInterface.
   */
  Filter(
      std::vector<std::pair<element_data_type, element_data_type>>& passbands,
      std::vector<std::pair<element_data_type, element_data_type>>& stopbands,
      element_data_type samplingFrequency,
      FastFourierTransformInterface<element_data_type>* fftClassInstance);

  /**
   * @brief Apply the filter to the given data.
   *
   * This function applies the filter to the provided input data based on the
   * configuration set by the arguments passed to the constructor.
   *
   * @param filterInput A vector that needs to be filtered.
   * @return The filtered output data.
   */
  std::vector<element_data_type> process(
      std::vector<element_data_type> filterInput) override;

 private:
  FastFourierTransformInterface<element_data_type>*
      fftClassInstance;  //!< The FastFourierTransformInterface instance.
};

template class Filter<double, double>;

#endif
