#include "SignalHistory.h"

#include <deque>

/**
 * @brief Constructs a new SignalHistory object.
 *
 * This constructor initializes an empty list with a size of arraySize.
 */
template <class element_type>
SignalHistory<element_type>::SignalHistory(element_type arraySize) {
  // Initialize the deque with a size of arraySize
  history.resize(arraySize);
};

/**
 * @brief Destructs a new SignalHistory object.
 *
 * This constructor deletes the empty list.
 */
template <class element_type>
SignalHistory<element_type>::~SignalHistory() {
  this->history.~deque();
};

/**
 * @brief Adds a signal to the history as a
 * @param signal The signal to be added to the history.
 *
 * If the history is full, remove the oldest signal before adding the new one.
 */
template <class element_type>
void SignalHistory<element_type>::put(element_type signal) {
  // If the history is full, remove the oldest signal
  if (history.size() == history.max_size()) {
    history.pop_front();
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
 * This function uses the at function to access the signal at the given index.
 * If the index is out of range, it throws an std::out_of_range exception.
 */
template <class element_type>
element_type SignalHistory<element_type>::get(element_type nthSample) {
  // Return the signal at the given index
  return history.at(nthSample);
};

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
  return history.size();
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
