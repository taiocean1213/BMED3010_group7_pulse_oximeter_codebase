#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

#include "signal_history/SignalHistoryInterface.h"

/**
 * @class SignalProcessor
 * @brief Forward declaration for signal processing.
 */
template <class element_type>
class SignalProcessor : public SignalHistoryInterface<element_type> {
 public:
  /**
   * @brief Puts a DC signal to the class.
   * @param signal The signal to be put.
   */
  void put(element_type signal) override;

  /**
   * @brief Gets a signal from the processor.
   * @param nthSample The index of the signal to be retrieved.
   * @return The signal at the specified index.
   */
  element_type get(size_t nthSample) override;

  /**
   * @brief Resets the processor.
   */
  void reset() override;

 private:
  /**
   * @brief Gets the entry point index.
   * @return The entry point index.
   */
  size_t getEntryPointIndex() override;

  /**
   * @brief Updates the entry point index.
   */
  void updateEntryPointIndex() override;
};

#endif