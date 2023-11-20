#ifndef FAST_FOURIER_TRANSFORM_INTERFACE_H
#define FAST_FOURIER_TRANSFORM_INTERFACE_H

#include <vector>

/**
 * @brief The FastFourierTransformInterface class is an abstract base class that
 * defines the interface for Fast Fourier Transform and Inverse Fast Fourier
 * Transform operations.
 * @tparam element_datatype The data type of the elements in the input and
 * output vectors.
 */
template <typename element_datatype>
class FastFourierTransformInterface {
 public:
  virtual ~FastFourierTransformInterface() {}
  /**
   * @brief Performs the Fast Fourier Transform operation on the input data.
   * @param realInput The input data vector for real part.
   * @param imaginaryInput The input data vector for imaginary part.
   * @param realOutput The output data vector for real part.
   * @param imaginaryOutput The output data vector for imaginary part.
   * @param sampleSize The sample size of the input data.
   */
  virtual void fastFourierTransform(
      const std::vector<element_datatype>* realInput,
      const std::vector<element_datatype>* imaginaryInput,
      std::vector<element_datatype>* realOutput,
      std::vector<element_datatype>* imaginaryOutput) = 0;

  /**
   * @brief Performs the Inverse Fast Fourier Transform operation on the input
   * data.
   * @param realInput The input data vector for real part.
   * @param imaginaryInput The input data vector for imaginary part.
   * @param realOutput The output data vector for real part.
   * @param imaginaryOutput The output data vector for imaginary part.
   * @param sampleSize The sample size of the input data.
   */
  virtual void inverseFastFourierTransform(
      const std::vector<element_datatype>* realInput,
      const std::vector<element_datatype>* imaginaryInput,
      std::vector<element_datatype>* realOutput,
      std::vector<element_datatype>* imaginaryOutput) = 0;
};

#endif
