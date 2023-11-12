#include "PPGSignalHardwareController.h"

#include <Arduino.h>

/**
 * @brief Gets the current time in microseconds.
 *
 * This function uses the Arduino micros function to get the current time in
 * microseconds.
 *
 * @return The current time in microseconds.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
auto PPGSignalHardwareController<voltage_data_type, time_data_type,
                                 pin_id_data_type>::getCurrentTimeUs()
    -> time_data_type {
  return micros();  // Returns the current time in microseconds.
}

/**
 * @brief Sets the voltage of the red LED.
 *
 * This function uses the Arduino analogWrite function to set the voltage of the
 * red LED.
 *
 * @param ledVoltage The voltage to set the red LED to.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void PPGSignalHardwareController<voltage_data_type, time_data_type,
                                 pin_id_data_type>::setRedLED(voltage_data_type
                                                                  ledVoltage) {
  analogWrite(5, ledVoltage);  // Sets the voltage of the red LED.
}

/**
 * @brief Sets the voltage of the infrared LED.
 *
 * This function uses the Arduino analogWrite function to set the voltage of the
 * infrared LED.
 *
 * @param ledVoltage The voltage to set the infrared LED to.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void PPGSignalHardwareController<
    voltage_data_type, time_data_type,
    pin_id_data_type>::setInfraRedLED(voltage_data_type ledVoltage) {
  analogWrite(6, ledVoltage);  // Sets the voltage of the infrared LED.
}

/**
 * @brief Gets the voltage of the photo diode.
 *
 * This function first uses the Arduino delay function to warm up the photo
 * diode, then uses the Arduino analogRead function to get the voltage of the
 * photo diode.
 *
 * @param photoDiodeWarmupTimeMs The time in milliseconds to warm up the photo
 * diode.
 * @return The voltage of the photo diode.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
auto PPGSignalHardwareController<voltage_data_type, time_data_type,
                                 pin_id_data_type>::
    getPhotoDiodeVoltage(time_data_type photoDiodeWarmupTimeMs)
        -> voltage_data_type {
  delay(photoDiodeWarmupTimeMs);  // Warms up the photo diode.
  return analogRead(A0);          // Returns the voltage of the photo diode.
}

// Explicit instantiation
template class PPGSignalHardwareController<int, unsigned long, int>;