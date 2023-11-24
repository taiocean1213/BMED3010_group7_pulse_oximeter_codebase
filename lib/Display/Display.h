#ifndef DISPLAY_H
#define DISPLAY_H

#ifndef EXCLUDEADAFRUITGFXLIB

#include <Adafruit_GFX.h>
#undef min
#undef max
#undef Min
#undef Max
#undef abs
#include <Adafruit_ILI9341.h>

#endif

#include "SignalHistory.h"
#include "user_interface/Displayinterface.h"

/**
 * @brief Class for the display functionality
 * @tparam values_data_type The data type of the value
 */
template <class values_data_type>
class Display : public DisplayInterface<values_data_type> {
 public:
  /**
   * @brief Constructor for the Display class
   */
  Display();

  /**
   * @brief Initialize the display
   */
  void begin() override;

  /**
   * @brief Update the SpO2 value on the display
   * @tparam values_data_type The data type of the SpO2 value
   * @param spo2_value The SpO2 value to be displayed
   */
  void updateSpO2(values_data_type spo2_value) override;

  /**
   * @brief Update the heart rate value on the display
   * @tparam values_data_type The data type of the heart rate value
   * @param hr_value The heart rate value to be displayed
   */
  void updateHBR(values_data_type hr_value) override;

  /**
   * @brief Update the PPG waveform on the display
   * @tparam values_data_type The data type of the PPG values
   * @param ppgWaveformClassPtr The pointerto the `SignalHistoryInterface`
   * template class containing the PPG waveform
   */
  void updatePPGWave(
      SignalHistoryInterface<values_data_type>* ppgWaveformClassPtr) override;

  /**
   * @brief Clear the display screen
   */
  void clearScreen() override;

 private:
  Adafruit_ILI9341* TFTscreenPtr;
};

// TODO explicit instantiation needed
template class Display<int>;
template class Display<float>;
template class Display<double>;

#endif