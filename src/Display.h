#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Example library for SSD1306 OLED display
#include <Arduino.h>

#include "user_interface/Displayinterface.h"


template <class values_data_type>
class Display : public DisplayInterface<values_data_type> {
public:
 /**
  * @brief Sets up the user interface.
  */
 void setupUI() override;

 /**
  * @brief Displays the heart rate.
  * @param heartRate The heart rate to display.
  */
 void displayHeartRate(values_data_type heartRate) override;

 /**
  * @brief Displays the SpO2 value.
  * @param spo2Value The SpO2 value to display.
  */
 void displaySpO2(values_data_type spo2Value) override;

 /**
  * @brief Displays a PPG data point.
  * @param ppgDataPoint The PPG data point to display.
  */
 void displayPPGDataPoint(values_data_type ppgDataPoint) override;
};

#endif