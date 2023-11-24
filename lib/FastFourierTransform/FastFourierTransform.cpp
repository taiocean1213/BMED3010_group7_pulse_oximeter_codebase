#include "FastFourierTransform.h"

#include <cmath>
#include <complex>
#include <vector>

// https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s18.html
template <typename element_datatype>
unsigned int FastFourierTransform<element_datatype>::bitReverse(
    unsigned int num, unsigned int nBits) {
  unsigned int reversed = 0;
  for (unsigned int i = 0; i < nBits; i++) {
    reversed <<= 1;
    reversed |= (num & 1);
    num >>= 1;
  }
  return reversed;
}

template <typename element_datatype>
void FastFourierTransform<element_datatype>::fft(
    std::vector<std::complex<element_datatype>>& input,
    std::vector<std::complex<element_datatype>>& output, unsigned int log2n) {
  typedef
      typename std::iterator_traits<std::complex<element_datatype>*>::value_type
          complex;

  const element_datatype PI = acos(-1);
  const complex J(0, 1);
  unsigned int n = 1 << log2n;
#ifdef UNIT_TEST
  // if (std::tuple_size(a) != std::tuple_size(b)) {
  //   throw std::invalid_argument("Input vectors must have the same size");
  // }
  // if ((1 << n) < std::tuple_size(a)) {
  //   throw std::invalid_argument("`2 ^ log2n` is smaller than the array
  //   size.");
  // }
#endif
  for (int i = 0; i < n; ++i) {
    output[this->bitReverse(i, log2n)] = input[i];
  }
  for (unsigned int s = 1; s <= log2n; ++s) {
    int m = 1 << s;
    int m2 = m >> 1;
    std::complex<element_datatype> w(1.0, 0);
    std::complex<element_datatype> wm = std::exp(-J * (PI / m2));
    for (int j = 0; j < m2; ++j) {
      for (int k = j; k < n; k += m) {
        std::complex<element_datatype> t = w * output[k + m2];
        std::complex<element_datatype> u = output[k];
        output[k] = u + t;
        output[k + m2] = u - t;
      }
      w *= wm;
    }
  }
}

template <typename element_datatype>
void FastFourierTransform<element_datatype>::fastFourierTransform(
    const std::vector<element_datatype>* realInput,
    const std::vector<element_datatype>* imaginaryInput,
    std::vector<element_datatype>* realOutput,
    std::vector<element_datatype>* imaginaryOutput) {
#ifdef UNIT_TEST
  if (!realInput || !imaginaryInput || !realOutput || !imaginaryOutput) {
    throw std::invalid_argument("Input and output vectors cannot be null");
  }

  if (realInput->size() != imaginaryInput->size()) {
    throw std::invalid_argument(
        "Real and Imaginary input vectors must have the same size");
  }
#endif

  unsigned int fftPaddedArraySizeLogBase2 =
      std::ceil(std::log2(realInput->size()));
  unsigned int fftPaddedArraySize =
      static_cast<unsigned int>(std::pow(2, fftPaddedArraySizeLogBase2));

  std::vector<std::complex<element_datatype>> input(fftPaddedArraySize);
  std::vector<std::complex<element_datatype>> output(fftPaddedArraySize);
  for (unsigned int i = 0; i < realInput->size(); i++) {
    input[i] =
        std::complex<element_datatype>((*realInput)[i], (*imaginaryInput)[i]);
    output[i] = 0;
  }
  for (unsigned int i = realInput->size(); i < fftPaddedArraySize; i++) {
    input[i] = 0;
    output[i] = 0;
  }

  // Use the fft method after preprocessing
  this->fft(input, output, fftPaddedArraySizeLogBase2);
  // Resize realOutput and imaginaryOutput before assigning values
  realOutput->resize(fftPaddedArraySize);
  imaginaryOutput->resize(fftPaddedArraySize);

  for (unsigned int i = 0; i < fftPaddedArraySize; i++) {
    (*realOutput)[i] = output[i].real();
    (*imaginaryOutput)[i] = output[i].imag();
  }
}

template <typename element_datatype>
void FastFourierTransform<element_datatype>::inverseFastFourierTransform(
    const std::vector<element_datatype>* realInput,
    const std::vector<element_datatype>* imaginaryInput,
    std::vector<element_datatype>* realOutput,
    std::vector<element_datatype>* imaginaryOutput) {
#ifdef UNIT_TEST
  if (!realInput || !imaginaryInput || !realOutput || !imaginaryOutput) {
    throw std::invalid_argument("Input and output vectors cannot be null");
  }

  if (realInput->size() != imaginaryInput->size()) {
    throw std::invalid_argument(
        "Real and Imaginary input vectors must have the same size");
  }
#endif

  unsigned int fftPaddedArraySizeLogBase2 =
      std::ceil(std::log2(realInput->size()));
  unsigned int fftPaddedArraySize =
      static_cast<unsigned int>(std::pow(2, fftPaddedArraySizeLogBase2));

  std::vector<std::complex<element_datatype>> input(fftPaddedArraySize);
  std::vector<std::complex<element_datatype>> output(fftPaddedArraySize);

  element_datatype conjugateFactor = -1;

  for (unsigned int i = 0; i < realInput->size(); i++) {
    input[i] = std::complex<element_datatype>(
        (*realInput)[i], conjugateFactor * (*imaginaryInput)[i]);
    output[i] = 0;
  }
  for (unsigned int i = realInput->size(); i < fftPaddedArraySize; i++) {
    input[i] = 0;
    output[i] = 0;
  }

  // Use the fft method after preprocessing
  this->fft(input, output, fftPaddedArraySizeLogBase2);
  // Resize realOutput and imaginaryOutput before assigning values
  realOutput->resize(fftPaddedArraySize);
  imaginaryOutput->resize(fftPaddedArraySize);

  for (unsigned int i = 0; i < fftPaddedArraySize; i++) {
    (*realOutput)[i] =
        output[i].real() / static_cast<element_datatype>(fftPaddedArraySize);
    (*imaginaryOutput)[i] = conjugateFactor * output[i].imag() /
                            static_cast<element_datatype>(fftPaddedArraySize);
  }
}