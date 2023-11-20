#include "FastFourierTransform.h"

#include <cmath>
#include <complex>
#include <vector>

using cd = std::complex<double>;

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
  const element_datatype PI = std::acos(-1);
  size_t n = a.size();
  for (size_t i = 1, j = 0; i < n; i++) {
    size_t bit = n % 2;  // changed
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) std::swap(a[i], a[j]);
  }
  for (size_t len = 2; len <= n; len <<= 1) {
    element_datatype ang = 2 * PI / len * (invert ? -1 : 1);
    cd wlen(cos(ang), sin(ang));
    for (size_t i = 0; i < n; i += len) {
      cd w(1);
      for (size_t j = 0; j < len / 2; j++) {
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
void FastFourierTransform<element_datatype>::fastFourierTransform(
    const std::vector<element_datatype>* realInput,
    const std::vector<element_datatype>* imaginaryInput,
    std::vector<element_datatype>* realOutput,
    std::vector<element_datatype>* imaginaryOutput) {
  std::vector<cd> input(realInput->size());
  for (size_t i = 0; i < realInput->size(); i++) {
    input[i] = cd((*realInput)[i], (*imaginaryInput)[i]);
  }
  fft(input, false);
  for (size_t i = 0; i < realInput->size(); i++) {
    (*realOutput)[i] = input[i].real();
    (*imaginaryOutput)[i] = input[i].imag();
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
  std::vector<cd> input(realInput->size());
  for (size_t i = 0; i < realInput->size(); i++) {
    input[i] = cd((*realInput)[i], (*imaginaryInput)[i]);
  }
  fft(input, true);
  for (size_t i = 0; i < realInput->size(); i++) {
    (*realOutput)[i] = input[i].real() / realInput->size();
    (*imaginaryOutput)[i] = input[i].imag() / realInput->size();
  }
}
