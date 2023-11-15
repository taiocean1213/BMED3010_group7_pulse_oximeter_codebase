#include "SignalHistory.h"

/**
 * @brief Constructs a new SignalHistory object.
 *
 * This constructor initializes an empty vector with a capacity of ARRAYSIZE.
 */
template <class element_type, element_type ARRAYSIZE>
SignalHistory<element_type, ARRAYSIZE>::SignalHistory() {
  // Initialize the vector with a capacity of ARRAYSIZE
  history.reserve(ARRAYSIZE);
}

/**
 * @brief Adds a signal to the history.
 *
 * @param signal The signal to be added to the history.
 *
 * If the history is full, remove the oldest signal before adding the new one.
 */
template <class element_type, element_type ARRAYSIZE>
void SignalHistory<element_type, ARRAYSIZE>::put(element_type signal) {
  // If the history is full, remove the oldest signal
  if (history.size() == ARRAYSIZE) {
    history.erase(history.begin());
  }
  // Add the new signal to the history
  history.push_back(signal);
}

/**
 * @brief Retrieves a signal from the history.
 *
 * @param nthSample The index of the signal to be retrieved from the history.
 * @return The signal at the given index.
 *
 * This function uses the at function to access the signal at the given index.
 * If the index is out of range, it throws an std::out_of_range exception.
 */
template <class element_type, element_type ARRAYSIZE>
element_type SignalHistory<element_type, ARRAYSIZE>::get(
    element_type nthSample) {
  // Return the signal at the given index
  return history.at(nthSample);
}

/**
 * @brief Resets the history.
 *
 * This function clears the history.
 */
template <class element_type, element_type ARRAYSIZE>
void SignalHistory<element_type, ARRAYSIZE>::reset() {
  // Clear the history
  history.clear();
}

/**
 * @brief Gets the entry point index.
 *
 * @return The entry point index.
 *
 * This function returns the index where the next signal will be stored in the
 * history. If the history is not full, it returns the current size of the
 * history. Otherwise, it returns 0.
 */
template <class element_type, element_type ARRAYSIZE>
element_type SignalHistory<element_type, ARRAYSIZE>::getEntryPointIndex() {
  // Return the index where the next signal will be stored in the history
  return std::min(history.size(), ARRAYSIZE);
}

/**
 * @brief Updates the entry point index.
 *
 * This function is not needed because the entry point index is automatically
 * updated when a signal is added to the history.
 */
template <class element_type, element_type ARRAYSIZE>
void SignalHistory<element_type, ARRAYSIZE>::updateEntryPointIndex() {
  // The entry point index is automatically updated when a signal is added to
  // the history
}
