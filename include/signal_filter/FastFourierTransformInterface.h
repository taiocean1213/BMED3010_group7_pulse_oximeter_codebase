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
   * @param input The input data vector.
   * @return The result of the Fast Fourier Transform operation.
   */
  virtual std::vector<element_datatype> fastFourierTransform(
      const std::vector<element_datatype> realInput,
      const std::vector<element_datatype> imaginaryInput,
      element_datatype sampleSize);

  /**
   * @brief Performs the Inverse Fast Fourier Transform operation on the input
   * data.
   * @param input The input data vector.
   * @return The result of the Inverse Fast Fourier Transform operation.
   */
  virtual std::vector<element_datatype> inverseFastFourierTransform(
      const std::vector<element_datatype> realInput,
      const std::vector<element_datatype> imaginaryInput,
      element_datatype sampleSize);
};

#endif