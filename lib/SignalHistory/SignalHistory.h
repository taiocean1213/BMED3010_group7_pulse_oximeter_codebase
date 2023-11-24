#ifndef SIGNAL_HISTORY_H
#define SIGNAL_HISTORY_H

#include <deque>
#include <vector>

#include "signal_history/SignalHistoryInterface.h"

/**
 * @brief Template class for storing history of discrete signal intensity.
 *
 * @tparam element_type The type of the signals.
 * @tparam ARRAYSIZE The maximum size of the history.
 */
template <class element_type>
class SignalHistory : public SignalHistoryInterface<element_type> {
 public:
  /**
   * @brief Constructs a new SignalHistory object.
   *
   * This constructor initializes an empty vector with a capacity of ARRAYSIZE.
   */
  SignalHistory();

  /**
   * @brief Destructs a new SignalHistory object.
   *
   * This Destructor deletes vector attributes of the class instance.
   */
  ~SignalHistory();

  /**
   * @brief Adds a signal to the history.
   *
   * @param signal The signal to be added to the history.
   *
   * If the history is full, remove the oldest signal before adding the new one.
   */
  void put(element_type signal) override;

  /**
   * @brief Retrieves a signal from the history.
   *
   * @param nthSample The index of the signal to be retrieved from the history.
   * @return The signal at the given index.
   *
   * This function uses the at function to access the signal at the given index.
   * If the index is out of range, it throws an std::out_of_range exception.
   */
  element_type get(element_type nthSample) override;

  /**
   * @brief Retrieves the smallest signal from the history.
   *
   * @return The smallest signal value.
   *
   */
  element_type min() override;

  /**
   * @brief Retrieves the largest signal from the history.
   *
   * @return The largest signal value.
   *
   */
  element_type max() override;

  /**
   * @brief Retrieves the number of samples stored for history.
   *
   * @return The number of samples stored for history.
   *
   */
  element_type size() override;

  /**
   * @brief Resets the history.
   *
   * This function clears the history.
   */
  void reset() override;

 private:
  /**
   * @brief Gets the entry point index.
   *
   * @return The entry point index.
   *
   * This function returns the index where the next signal will be stored in the
   * history. If the history is not full, it returns the current size of the
   * history. Otherwise, it returns 0.
   */
  element_type getEntryPointIndex() override;

  /**
   * @brief Updates the entry point index.
   *
   * This function is not needed because the entry point index is automatically
   * updated when a signal is added to the history.
   */
  void updateEntryPointIndex() override;

 private:
  std::deque<element_type> history;  // The history of signals
};

template class SignalHistory<double>;

#endif
