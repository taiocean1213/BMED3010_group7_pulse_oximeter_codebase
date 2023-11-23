#include "SignalHistory.h"

// if needed, `#include <stdexcept>` can Include this header file to use
// the `std::out_of_range`
#include <algorithm>
#include <vector>

#ifdef UNIT_TEST
#include <stdexcept>  // std::invalid_argument
#endif

/**
 * @brief Constructs a new SignalHistory object.
 *
 * This constructor initializes an empty vector with a size of arraySize.
 *
 * @param arraySize The size of the vector.
 */
template <class element_type>
SignalHistory<element_type>::SignalHistory(element_type arraySize) {
  // Initialize the vector with a size of arraySize
  history.resize(arraySize);
};

/**
 * @brief Destructs a new SignalHistory object.
 *
 * This destructor is automatically called when the vector goes out of scope,
 * so there's no need to manually call the destructor of the vector.
 */
template <class element_type>
SignalHistory<element_type>::~SignalHistory(){
    // The destructor of the vector is automatically called when the vector goes
    // out of scope
};

/**
 * @brief Adds a signal to the history.
 *
 * If the history is full, remove the oldest signal before adding the new one.
 *
 * @param signal The signal to be added to the history.
 */
template <class element_type>
void SignalHistory<element_type>::put(element_type signal) {
  // If the history is full, remove the oldest signal
  if (history.size() == history.max_size()) {
    history.erase(history.begin());
  }
  // Add the new signal to the history
  history.push_back(signal);
};

/**
 * @brief Retrieves a signal from the history.
 *
 * @param nthSample The index of the signal to be retrieved from the history.
 * @return The signal at the given index.
 *
 * This function checks if nthSample is a valid index before calling the at
 * function. If nthSample is not a valid index, it throws an std::out_of_range
 * exception.
 */
template <class element_type>
element_type SignalHistory<element_type>::get(element_type nthSample) {
#ifdef UNIT_TEST
  // Check if nthSample is a valid index
  if (nthSample >= history.size()) {
    throw std::invalid_argument(
        "Input and output vectors must be of the same size");
  }
#endif

  return history.at(nthSample);
};

/**
 * @brief Retrieves the smallest signal from the history.
 *
 * @return The smallest signal value.
 *
 */
template <class element_type>
element_type SignalHistory<element_type>::min() {
#ifdef UNIT_TEST
  // Check if history is empty
  if (history.empty()) {
    throw std::runtime_error("History is empty");
  }
#endif
  // Return the smallest signal in the history
  return *std::min_element(history.begin(), history.end());
};

/**
 * @brief Retrieves the largest signal from the history.
 *
 * @return The largest signal value.
 *
 */
template <class element_type>
element_type SignalHistory<element_type>::max() {
#ifdef UNIT_TEST
  // Check if history is empty
  if (history.empty()) {
    throw std::runtime_error("History is empty");
  }
#endif
  // Return the largest signal in the history
  return *std::max_element(history.begin(), history.end());
};

/**
 * @brief Retrieves the number of samples stored for history.
 *
 * @return The number of samples stored for history.
 *
 */
template <class element_type>
element_type SignalHistory<element_type>::size() {
  return history.size();
}

/**
 * @brief Resets the history.
 *
 * This function clears the history.
 */
template <class element_type>
void SignalHistory<element_type>::reset() {
  // Clear the history
  history.clear();
};

/**
 * @brief Gets the entry point index.
 *
 * @return The entry point index.
 *
 * This function returns the index where the next signal will be stored in the
 * history. If the history is not full, it returns the current size of the
 * history. Otherwise, it returns 0.
 */
template <class element_type>
element_type SignalHistory<element_type>::getEntryPointIndex() {
  // Return the index where the next signal will be stored in the history
  // If the history is full, return 0
  if (history.size() == history.max_size()) {
    return 0;
  } else {
    return history.size();
  }
};

/**
 * @brief Updates the entry point index.
 *
 * This function is not needed because the entry point index is automatically
 * updated when a signal is added to the history.
 */
template <class element_type>
void SignalHistory<element_type>::updateEntryPointIndex(){
    // The entry point index is automatically updated when a signal is added to
    // the history
};
