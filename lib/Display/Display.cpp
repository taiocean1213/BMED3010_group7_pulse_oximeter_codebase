#include "Display.h"

#ifndef EXCLUDEADAFRUITGFXLIB

// Include the Adafruit GFX library for drawing graphics
#include <Adafruit_GFX.h>
#undef min
#undef max
#undef Min
#undef Max
#undef abs
// Include the Adafruit ILI9341 library for interacting with the ILI9341 TFT
// display
#include <Adafruit_ILI9341.h>

#endif

// Define the Chip Select (CS), Data/Command (DC), and Reset (RST) pins for the
// ILI9341 TFT display
#define _cs 10
#define _dc 8
#define _rst 9

/**
 * @brief Constructor for the Display class
 */
template <class values_data_type>
Display<values_data_type>::Display() {
  TFTscreenPtr = new Adafruit_ILI9341(_cs, _dc, _rst);
}

/**
 * @brief Initialize the display
 */
template <class values_data_type>
void Display<values_data_type>::begin() {
  // Begin the SPI communication
  SPI.begin();
  // Begin the TFT screen
  TFTscreenPtr->begin();
  // Set the rotation of the screen to 3
  TFTscreenPtr->setRotation(3);
  // Fill the screen with black color
  TFTscreenPtr->fillScreen(ILI9341_BLACK);
  Serial.println("begin()");
};
/**
 * @brief Update the SpO2 value on the display
 * @tparam values_data_type The data type of the SpO2 value
 * @param spo2_value The SpO2 value to be displayed
 */
template <class values_data_type>
void Display<values_data_type>::updateSpO2(values_data_type spo2_value) {
  // Set the cursor position to the top left corner of the screen
  TFTscreenPtr->setCursor(0, 0);
  // Set the text color to white
  TFTscreenPtr->setTextColor(ILI9341_WHITE);
  // Set the text size to 2
  TFTscreenPtr->setTextSize(2);
  // Print the string "SpO2: "
  TFTscreenPtr->print("SpO2: ");
  // Print the SpO2 value
  TFTscreenPtr->print(spo2_value);
  Serial.println("spo2()");
};
/**
 * @brief Update the heart beat rate value on the display
 * @tparam values_data_type The data type of the heart rate value
 * @param hr_value The heart rate value to be displayed
 */
template <class values_data_type>
void Display<values_data_type>::updateHBR(values_data_type hr_value) {
  // Calculate the half of the screen width
  int half_screen_width = TFTscreenPtr->width() / 2;
  // Set the cursor position to the middle of the screen
  TFTscreenPtr->setCursor(half_screen_width, 0);
  // Set the text color to white
  TFTscreenPtr->setTextColor(ILI9341_WHITE);
  // Set the text size to 2
  TFTscreenPtr->setTextSize(2);
  // Print the string "HR: "
  TFTscreenPtr->print("HR: ");
  // Print the heart rate value
  TFTscreenPtr->print(hr_value);
  Serial.println("HR()");
};
/**
 * @brief Update the PPG waveform on the display
 * @tparam values_data_type The data type of the PPG values
 * @param ppg_values An array of PPG values
 * @param num_values The number of PPG values in the array
 * @param min_ppg_value The minimum PPG value
 * @param max_ppg_value The maximum PPG value
 */
template <class values_data_type>
void Display<values_data_type>::updatePPGWave(
    SignalHistoryInterface<values_data_type>* ppgWaveformClassPtr) {
  // Define the color for the bars
  const uint16_t BAR_COLOR = ILI9341_WHITE;

  // Calculate the width of each bar
  int bar_width = TFTscreenPtr->width() / ppgWaveformClassPtr->size();

  // Calculate the half of the screen height
  int half_screen_height = TFTscreenPtr->height() / 2;

  // Loop over each PPG value
  for (int i = 0; i < ppgWaveformClassPtr->size(); i++) {
    // Map the PPG value to the screen height
    int bar_height =
        map(ppgWaveformClassPtr->get(i), ppgWaveformClassPtr->min(),
            ppgWaveformClassPtr->max(), 0, half_screen_height);

    // Ensure the bar height is not negative
    if (bar_height < 0) bar_height = 0;

    // Calculate the y position of the bar
    int bar_y = half_screen_height - bar_height;

    // Draw the bar on the screen
    TFTscreenPtr->fillRect(i * bar_width, bar_y, bar_width, bar_height,
                           BAR_COLOR);
  }
  Serial.println("PPG()");
};
/**
 * @brief Clear the display screen
 */
template <class values_data_type>
void Display<values_data_type>::clearScreen() {
  // Fill the screen with black color
  TFTscreenPtr->fillScreen(ILI9341_BLACK);
}