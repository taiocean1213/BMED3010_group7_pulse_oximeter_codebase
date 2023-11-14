#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include "user_interface/Displayinterface.h"

/**
 * @class Display
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
   * @param ppg_values An array of PPG values
   * @param num_values The number of PPG values in the array
   * @param min_ppg_value The minimum PPG value
   * @param max_ppg_value The maximum PPG value
   */
  void updatePPGWave(values_data_type ppg_values[], int num_values,
                     values_data_type min_ppg_value,
                     values_data_type max_ppg_value) override;

  /**
   * @brief Clear the display screen
   */
  void clearScreen() override;

 private:
  Adafruit_ILI9341 TFTscreen;
};

// TODO explicit instantiation needed

#endif