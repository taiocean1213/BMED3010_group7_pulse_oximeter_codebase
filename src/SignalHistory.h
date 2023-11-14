#ifndef SIGNALHISTORY_H
#define SIGNALHISTORY_H

#include "signal_history/SignalHistoryInterface.h"

/**
 * @class SignalHistory
 * @brief Concrete implementation of the SignalHistory class for a pulse
 * oximeter.
 *
 * This class provides a concrete implementation of the SignalHistory class for
 * a pulse oximeter. It stores the history of pulse and oxygen saturation
 * signals.
 *
 * @tparam element_type The type of signal to be stored in the history, such as
 * pulse or oxygen saturation.
 */
template <class element_type, element_type ARRAYSIZE>
class SignalHistory : public SignalHistoryInterface<element_type> {
 public:
  /**
   * @brief Default constructor for SignalHistory.
   */
  SignalHistory();
  /**
   * @brief Puts a signal into the history.
   *
   * @param signal The signal to be put into the history.
   * This could be a pulse or oxygen saturation signal.
   */
  void put(element_type signal) override;

  /**
   * @brief Gets a signal from the history.
   *
   * @param nthSample The index of the signal to be retrieved from the history.
   * @return The signal at the given index.
   * This could be a pulse or oxygen saturation signal.
   */
  element_type get(element_type nthSample) override;

  /**
   * @brief Resets the history.
   * This could be useful when the pulse oximeter needs to start measuring from
   * a clean state.
   */
  void reset() override;

 private:
  /**
   * @brief Gets the entry point index.
   *
   * @return The entry point index.
   * This could be the index where the next signal will be stored in the
   * history.
   */
  element_type getEntryPointIndex() override;

  /**
   * @brief Updates the entry point index.
   * This could be used after a signal is put into the history, to update the
   * index for the next signal.
   */
  void updateEntryPointIndex() override;
};

// Explicit instantiation is needed

#endif
