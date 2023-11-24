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
 * @tparam signal_period_datatype The data type of the time period values in
 * microseconds.
 */
template <typename element_data_type, typename signal_period_datatype>
class Filter
    : public FilterInterface<element_data_type, signal_period_datatype> {
 public:
  /**
   * @brief Constructor of the Filter class.
   *
   * This constructor initializes the filter with the provided passbands,
   * stopbands, sampling frequency, and FFT instance.
   *
   * @param passbands The vector of pairs representing the passbands.
   * @param stopbands The vector of pairs representing the stopbands.
   * @param samplingPeriodUs The sampling period of the signal in microseconds.
   * @param fft The instance of the FastFourierTransformInterface.
   */
  Filter(
      std::vector<std::pair<element_data_type, element_data_type>>& passbands,
      std::vector<std::pair<element_data_type, element_data_type>>& stopbands,
      element_data_type samplingPeriodUs,
      FastFourierTransformInterface<element_data_type>* fftClassInstance);

  /**
   * @brief Apply the filter to the given data based on the configuration set by
   * the arguments passed to the constructor.
   *
   * @param filterInput The input data to be filtered.
   * @param filterOutput The output data after filtering.
   */
  void process(
      SignalHistoryInterface<element_data_type>* filterInputPtr,
      SignalHistoryInterface<element_data_type>* filterOutputPtr) override;

 private:
  FastFourierTransformInterface<element_data_type>*
      fftClassInstancePtr;  //!< The FastFourierTransformInterface instance.

  element_data_type samplingPeriodUs;
  std::vector<std::pair<element_data_type, element_data_type>> passbands;
  std::vector<std::pair<element_data_type, element_data_type>> stopbands;

  bool isInPassband(
      element_data_type frequency,
      const std::vector<std::pair<element_data_type, element_data_type>>&
          passbands);
  bool isInStopband(
      element_data_type frequency,
      const std::vector<std::pair<element_data_type, element_data_type>>&
          stopbands);
};

template class Filter<double, int>;
template class Filter<double, double>;

#endif
