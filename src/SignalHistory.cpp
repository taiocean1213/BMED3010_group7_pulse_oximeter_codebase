#include "SignalHistory.h"

/**
 * @brief Implementation of the default constructor for SignalHistory.
 */
template <class element_type, element_type ARRAYSIZE>
SignalHistory<element_type, ARRAYSIZE>::SignalHistory() {
  // Implementation of constructor
}

/**
 * @brief Puts a signal into the history.
 *
 * @param signal The signal to be put into the history.
 * This could be a pulse or oxygen saturation signal.
 */
template <class element_type, element_type ARRAYSIZE>
void SignalHistory<element_type, ARRAYSIZE>::put(element_type signal) {
  // Implementation of put method
}

/**
 * @brief Gets a signal from the history.
 *
 * @param nthSample The index of the signal to be retrieved from the history.
 * @return The signal at the given index.
 * This could be a pulse or oxygen saturation signal.
 */
template <class element_type, element_type ARRAYSIZE>
element_type SignalHistory<element_type, ARRAYSIZE>::get(
    element_type nthSample) {
  // Implementation of get method
}

/**
 * @brief Resets the history.
 * This could be useful when the pulse oximeter needs to start measuring from
 * a clean state.
 */
template <class element_type, element_type ARRAYSIZE>
void SignalHistory<element_type, ARRAYSIZE>::reset() {
  // Implementation of reset method
}

/**
 * @brief Gets the entry point index.
 *
 * @return The entry point index.
 * This could be the index where the next signal will be stored in the
 * history.
 */
template <class element_type, element_type ARRAYSIZE>
element_type SignalHistory<element_type, ARRAYSIZE>::getEntryPointIndex() {
  // Implementation of getEntryPointIndex method
}

/**
 * @brief Updates the entry point index.
 * This could be used after a signal is put into the history, to update the
 * index for the next signal.
 */
template <class element_type, element_type ARRAYSIZE>
void SignalHistory<element_type, ARRAYSIZE>::updateEntryPointIndex() {
  // Implementation of updateEntryPointIndex method
}
