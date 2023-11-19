#ifndef FAST_FOURIER_TRANSFORM_H
#define FAST_FOURIER_TRANSFORM_H

#include <complex>
#include <vector>

#include "signal_filter/FastFourierTransformInterface.h"

using cd = std::complex<double>;

/**
 * @brief The FastFourierTransform class is a concrete implementation of the
 * FastFourierTransformInterface class that uses the arduinoFFT library to
 * perform Fast Fourier Transform and Inverse Fast Fourier Transform operations.
 * @tparam element_datatype The data type of the elements in the input and
 * output vectors.
 */
template <typename element_datatype>
class FastFourierTransform
    : public FastFourierTransformInterface<element_datatype> {
 public:
  /**
   * @brief Performs the Fast Fourier Transform operation on the input data.
   * @param input The input data vector.
   * @return The result of the Fast Fourier Transform operation.
   */
  std::vector<element_datatype> fastFourierTransform(
      const std::vector<element_datatype> realInput,
      const std::vector<element_datatype> imaginaryInput,
      element_datatype sampleSize) override;

  /**
   * @brief Performs the Inverse Fast Fourier Transform operation on the input
   * data.
   * @param input The input data vector.
   * @return The result of the Inverse Fast Fourier Transform operation.
   */
  std::vector<element_datatype> inverseFastFourierTransform(
      const std::vector<element_datatype> realInput,
      const std::vector<element_datatype> imaginaryInput,
      element_datatype sampleSize) override;

 private:
  static void fft(std::vector<cd>& a, bool invert);
};

// Explicit instantiation
template class FastFourierTransform<float>;
template class FastFourierTransform<double>;

#endif
