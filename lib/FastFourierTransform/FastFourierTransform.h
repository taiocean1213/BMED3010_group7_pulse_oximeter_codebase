#ifndef FAST_FOURIER_TRANSFORM_H
#define FAST_FOURIER_TRANSFORM_H

#include <complex>
#include <iterator>

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
   * @brief Performs the Fast Fourier Transform operation on the input data and
   * returns the result to the address with `2 ^ realInput.length()` elements.
   * @param realInput The input data vector for real part.
   * @param imaginaryInput The input data vector for imaginary part.
   * @param realOutput The output data vector for real part.
   * @param imaginaryOutput The output data vector for imaginary part.
   */

  void fastFourierTransform(
      const std::vector<element_datatype>* realInput,
      const std::vector<element_datatype>* imaginaryInput,
      std::vector<element_datatype>* realOutput,
      std::vector<element_datatype>* imaginaryOutput) override;

  /**
   * @brief Performs the Inverse Fast Fourier Transform operation on the input
   * data and returns the result to the address with `2 ^ realInput.length()`
   * elements.
   * @param realInput The input data vector for real part.
   * @param imaginaryInput The input data vector for imaginary part.
   * @param realOutput The output data vector for real part.
   * @param imaginaryOutput The output data vector for imaginary part.
   * @param sampleSize The sample size of the input data.
   */

  void inverseFastFourierTransform(
      const std::vector<element_datatype>* realInput,
      const std::vector<element_datatype>* imaginaryInput,
      std::vector<element_datatype>* realOutput,
      std::vector<element_datatype>* imaginaryOutput) override;

 private:
  /**
   * @brief FIXME A static function to perform FFT on the input data.
   * @param a The input data vector.
   * @param invert A boolean indicating whether to perform FFT or inverse FFT.
   */
  void fft(std::vector<std::complex<element_datatype>>& a,
           std::vector<std::complex<element_datatype>>& b, unsigned int log2n);
  unsigned int bitReverse(unsigned int num, unsigned int nBits);
};

// Explicit instantiation
template class FastFourierTransform<float>;
template class FastFourierTransform<double>;

#endif
