// FastFourierTransform.cpp
#include "FastFourierTransform.h"

#include <cmath>
#include <complex>
#include <vector>

using cd = std::complex<double>;
const double PI = std::acos(-1);

// https://cp-algorithms.com/algebra/fft.html#improved-implementation-in-place-computation
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

// https://cp-algorithms.com/algebra/fft.html#improved-implementation-in-place-computation
template <typename element_datatype>
std::vector<element_datatype>
FastFourierTransform<element_datatype>::fastFourierTransform(
    const std::vector<element_datatype> realInput,
    const std::vector<element_datatype> imaginaryInput,
    element_datatype sampleSize) {
  std::vector<cd> input(sampleSize);
  for (int i = 0; i < sampleSize; i++) {
    input[i] = cd(realInput[i], imaginaryInput[i]);
  }
  fft(input, false);
  std::vector<element_datatype> result(sampleSize);
  for (int i = 0; i < sampleSize; i++) {
    result[i] = input[i].real();
  }
  return result;
}

// https://cp-algorithms.com/algebra/fft.html#improved-implementation-in-place-computation
template <typename element_datatype>
std::vector<element_datatype>
FastFourierTransform<element_datatype>::inverseFastFourierTransform(
    const std::vector<element_datatype> realInput,
    const std::vector<element_datatype> imaginaryInput,
    element_datatype sampleSize) {
  std::vector<cd> input(sampleSize);
  for (int i = 0; i < sampleSize; i++) {
    input[i] = cd(realInput[i], imaginaryInput[i]);
  }
  fft(input, true);
  std::vector<element_datatype> result(sampleSize);
  for (int i = 0; i < sampleSize; i++) {
    result[i] = input[i].real() / sampleSize;
  }
  return result;
}
