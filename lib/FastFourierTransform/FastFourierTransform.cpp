#include "FastFourierTransform.h"

#include <cmath>
#include <complex>
#include <vector>

using cd = std::complex<double>;
const double PI = std::acos(-1);

/**
 * @brief A static function to perform FFT on the input data.
 * Modified from from
 * https://cp-algorithms.com/algebra/fft.html#improved-implementation-in-place-computation
 *
 * @param a The input data vector.
 * @param invert A boolean indicating whether to perform FFT or inverse FFT.
 */
template <typename element_datatype>
void FastFourierTransform<element_datatype>::fft(std::vector<cd>& a,
                                                 bool invert) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) std::swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : 1);
    cd wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      cd w(1);
      for (int j = 0; j < len / 2; j++) {
        cd u = a[i + j], v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if (invert) {
    for (cd& x : a) x /= n;
  }
}

/**
 * @brief Performs the Fast Fourier Transform operation on the input
 * data. Modified from
 * https://cp-algorithms.com/algebra/fft.html#improved-implementation-in-place-computation
 *
 * @param realInput The input data vector for real part.
 * @param imaginaryInput The input data vector for imaginary part.
 * @param realOutput The output data vector for real part.
 * @param imaginaryOutput The output data vector for imaginary part.
 */
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
    throw std::invalid_argument("Input vectors must have the same size");
  }
#endif

  std::vector<cd> input(realInput->size());
  for (size_t i = 0; i < realInput->size(); i++) {
    input[i] = cd((*realInput)[i], (*imaginaryInput)[i]);
  }
  fft(input, false);

  // Resize realOutput and imaginaryOutput before assigning values
  realOutput->resize(realInput->size());
  imaginaryOutput->resize(imaginaryInput->size());

  for (size_t i = 0; i < realInput->size(); i++) {
    (*realOutput)[i] = input[i].real();       // FIXME seg fault
    (*imaginaryOutput)[i] = input[i].imag();  // FIXME seg fault
  }
}

/**
 * @brief Performs the Inverse Fast Fourier Transform operation on the input
 * data. Modified from
 * https://cp-algorithms.com/algebra/fft.html#improved-implementation-in-place-computation
 *
 * @param realInput The input data vector for real part.
 * @param imaginaryInput The input data vector for imaginary part.
 * @param realOutput The output data vector for real part.
 * @param imaginaryOutput The output data vector for imaginary part.
 */
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
    throw std::invalid_argument("Input vectors must have the same size");
  }
#endif
  std::vector<cd> input(realInput->size());
  for (size_t i = 0; i < realInput->size(); i++) {
    input[i] = cd((*realInput)[i], (*imaginaryInput)[i]);
  }
  fft(input, true);

  // Resize realOutput and imaginaryOutput before assigning values
  realOutput->resize(realInput->size());
  imaginaryOutput->resize(imaginaryInput->size());

  for (size_t i = 0; i < realInput->size(); i++) {
    (*realOutput)[i] = input[i].real() / realInput->size();  // FIXME seg fault
    (*imaginaryOutput)[i] =
        input[i].imag() / realInput->size();  // FIXME seg fault
  }
}