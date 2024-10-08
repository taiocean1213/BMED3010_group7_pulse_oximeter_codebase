#ifndef SIGNAL_HISTORY_INTERFACE_H
#define SIGNAL_HISTORY_INTERFACE_H

/**
 * @interface SignalHistoryInterface
 * @brief Template class for storing history of discrete signal intensity.
 *
 * @tparam element_type The type of the signals.
 */
template <class element_type>
class SignalHistoryInterface {
 public:
  virtual ~SignalHistoryInterface() {}
  /**
   * @brief Adds a signal to the history.
   *
   * @param signal The signal to be added to the history.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual void put(element_type signal) = 0;

  /**
   * @brief Retrieves a signal from the history.
   *
   * @param nthSample The index of the signal to be retrieved from the history.
   * @return The signal at the given index.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual element_type get(element_type nthSample) = 0;

  /**
   * @brief Retrieves the smallest signal from the history.
   *
   * @return The smallest signal value.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual element_type min() = 0;

  /**
   * @brief Retrieves the largest signal from the history.
   *
   * @return The largest signal value.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual element_type max() = 0;

  /**
   * @brief Retrieves the number of samples stored for history.
   *
   * @return The number of samples stored for history.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual element_type size() = 0;

  /**
   * @brief Resets the history.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual void reset() = 0;

 private:
  /**
   * @brief Gets the entry point index.
   *
   * @return The entry point index.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual element_type getEntryPointIndex() = 0;

  /**
   * @brief Updates the entry point index.
   *
   * This is a pure virtual function, it must be overridden in any non-abstract
   * child class.
   */
  virtual void updateEntryPointIndex() = 0;
};

#endif  // SIGNAL_HISTORY_INTERFACE_H
