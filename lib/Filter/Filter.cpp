#include "Filter.h"

#ifdef UNIT_TEST
#include <stdexcept>
#endif
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
template <typename element_data_type, typename signal_period_datatype>
Filter<element_data_type, signal_period_datatype>::Filter(
    std::vector<std::pair<element_data_type, element_data_type>>& passbands,
    std::vector<std::pair<element_data_type, element_data_type>>& stopbands,
    element_data_type samplingPeriodUs,
    FastFourierTransformInterface<element_data_type>* fftClassInstanceParam) {
#ifdef UNIT_TEST
  if (fftClassInstanceParam == nullptr) {
    throw std::invalid_argument("fftClassInstanceParam cannot be null");
  }
#endif

  // Set the FFT instance
  this->fftClassInstancePtr = fftClassInstanceParam;
  // Set the sampling period
  this->samplingPeriodUs = samplingPeriodUs;

  // Copy the passbands and stopbands vectors to the class attributes
  this->passbands.assign(passbands.begin(), passbands.end());
  this->stopbands.assign(stopbands.begin(), stopbands.end());
}
/**
 * @brief Generate a vector of frequencies for a signal of size n.
 *
 * This function generates a vector of frequencies for a signal of size n. The
 * frequencies are calculated following the convention of np.fft.fftfreq in
 * Python's NumPy library. The first half of the frequencies are positive and
 * the second half are negative.
 *
 * @tparam element_data_type The type of the numbers in the vector.
 * @param n The size of the signal.
 * @return A vector of frequencies.
 */
template <typename element_data_type, typename signal_period_datatype>
std::vector<element_data_type>
Filter<element_data_type, signal_period_datatype>::fftfreq(unsigned int n) {
  std::vector<element_data_type> freq(n);
  unsigned int d = 1.0 / n;
  for (unsigned int i = 0; i < n / 2; ++i) {
    freq[i] = i * d;
  }
  for (unsigned int i = n / 2; i < n; ++i) {
    freq[i] = (i - n) * d;
  }
  return freq;
}

/**
 * @brief Apply the filter to the given data based on the configuration set by
 * the arguments passed to the constructor.
 *
 * @param filterInput The input data to be filtered.
 * @param filterOutput The output data after filtering.
 */
template <typename element_data_type, typename signal_period_datatype>
void Filter<element_data_type, signal_period_datatype>::process(
    SignalHistoryInterface<element_data_type>* filterInputPtr,
    SignalHistoryInterface<element_data_type>* filterOutputPtr) {
#ifdef UNIT_TEST
  if (filterInputPtr == nullptr || filterOutputPtr == nullptr) {
    throw std::invalid_argument(
        "filterInputPtr and filterOutputPtr cannot be null");
  }
#endif

  // Retrieve the signal history from the input filter
  element_data_type historySize =
      static_cast<element_data_type>(filterInputPtr->size());
  std::vector<element_data_type> realInput(historySize),
      imaginaryInput(historySize);
  for (std::size_t i = 0; i < historySize; ++i) {
    realInput[i] = filterInputPtr->get(i);
    imaginaryInput[i] = 0;  // Assume that the imaginary part is always 0
  }

  // Perform FFT on the input data
  std::vector<element_data_type> realOutput, imaginaryOutput;
  fftClassInstancePtr->fastFourierTransform(&realInput, &imaginaryInput,
                                            &realOutput, &imaginaryOutput);

  // Array size check.
#ifdef UNIT_TEST
  if (realOutput.size() == imaginaryOutput.size()) {
    throw std::invalid_argument(
        "realOutput and imaginaryOutput have different size.");
  }
#endif

  //  Get the frequencies in the frequency
  std::vector<element_data_type> fftFrequency =
      this->fftfreq(static_cast<unsigned int>(realOutput.size()));

  // Modify the frequency components according to the passbands and stopbands
  for (std::size_t i = 0; i < realOutput.size(); ++i) {
    element_data_type fftFrequencyIter = fftFrequency[i];

    if (isInPassband(fftFrequencyIter, stopbands)) continue;

    realOutput[i] = 0;
    imaginaryOutput[i] = 0;

#ifdef UNIT_TEST
    if (!isInStopband(fftFrequencyIter, stopbands)) {
      throw std::invalid_argument(
          "Frequency not placed in passband or stopband");
    }
#endif
  }

  return;
  // Perform inverse FFT on the modified frequency components
  std::vector<element_data_type> realOutputInverse, imaginaryOutputInverse;
  fftClassInstancePtr->inverseFastFourierTransform(
      &realOutput, &imaginaryOutput, &realOutputInverse,
      &imaginaryOutputInverse);

  // Store the filtered signal
  for (std::size_t i = 0; i < realInput.size(); ++i) {
    filterOutputPtr->put(realOutputInverse[i]);
  }

  // Free all the memory
  realInput.clear();
  imaginaryInput.clear();
  realOutput.clear();
  imaginaryOutput.clear();
  realOutputInverse.clear();
  imaginaryOutputInverse.clear();
  fftFrequency.clear();

  realInput.shrink_to_fit();
  imaginaryInput.shrink_to_fit();
  realOutput.shrink_to_fit();
  imaginaryOutput.shrink_to_fit();
  realOutputInverse.shrink_to_fit();
  imaginaryOutputInverse.shrink_to_fit();
  fftFrequency.shrink_to_fit();

  return;
}

/**
 * @brief Check if a frequency is in the passband.
 *
 * @param frequency The frequency to check.
 * @param passbands The vector of pairs representing the passbands.
 * @return true if the frequency is in the passband, false otherwise.
 */
template <typename element_data_type, typename signal_period_datatype>
bool Filter<element_data_type, signal_period_datatype>::isInPassband(
    element_data_type frequency,
    const std::vector<std::pair<element_data_type, element_data_type>>&
        passbands) {
  for (const auto& passband : passbands) {
    if (frequency >= passband.first && frequency <= passband.second) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Check if a frequency is in the stopband.
 *
 * @param frequency The frequency to check.
 * @param stopbands The vector of pairs representing the stopbands.
 * @return true if the frequency is in the stopband, false otherwise.
 */
template <typename element_data_type, typename signal_period_datatype>
bool Filter<element_data_type, signal_period_datatype>::isInStopband(
    element_data_type frequency,
    const std::vector<std::pair<element_data_type, element_data_type>>&
        stopbands) {
  for (const auto& stopband : stopbands) {
    if (frequency >= stopband.first && frequency <= stopband.second) {
      return true;
    }
  }
  return false;
}
