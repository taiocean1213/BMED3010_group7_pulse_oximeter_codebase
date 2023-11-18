#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H
#include "signal_history/SignalHistoryInterface.h"

/**
 * @interface DisplayInterface
 * @brief Abstract interface for the display functionality
 */
template <class values_data_type>
class DisplayInterface {
 public:
  /**
   * @brief Virtual destructor for the DisplayInterface class
   */
  virtual ~DisplayInterface() {}

  /**
   * @brief Initialize the display
   */
  virtual void begin() = 0;

  /**
   * @brief Update the SpO2 value on the display
   * @tparam values_data_type The data type of the SpO2 value
   * @param spo2_value The SpO2 value to be displayed
   */
  virtual void updateSpO2(values_data_type spo2_value) = 0;

  /**
   * @brief Update the heart rate value on the display
   * @tparam values_data_type The data type of the heart rate value
   * @param hr_value The heart rate value to be displayed
   */
  virtual void updateHBR(values_data_type hr_value) = 0;

  /**
   * @brief Update the PPG waveform on the display
   * @tparam values_data_type The data type of the PPG values
   * @param ppgWaveformClassPtr The pointerto the `SignalHistoryInterface`
   * template class containing the PPG waveform
   */
  virtual void updatePPGWave(
      SignalHistoryInterface<values_data_type>* ppgWaveformClassPtr) = 0;

  /**
   * @brief Clear the display screen
   */
  virtual void clearScreen() = 0;
};

#endif