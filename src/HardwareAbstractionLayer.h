#ifndef HARDWAREABSTRACTIONLAYER_H
#define HARDWAREABSTRACTIONLAYER_H

#include <Arduino.h>

#include "hardware_driver_apis/HardwareAbstractionLayerInterface.h"

template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class HardwareAbstractionLayer {
 public:
  /**
   * @brief Constructors that configures the hardware input and output
   *
   * @param analogResolutionValue The number of quantized level is
   * set to `2 ^ (analogResolutionValue)`.
   * @param baudRate The baud rate that is set for communication via
   * the serial port.
   */
  HardwareAbstractionLayer(int analogResolutionValue, int baudRate);

  /**
   * @brief Configures a pin t either output or input mode.
   * @param outputPinId The ID of the pin that needs to be configured.
   * @param outputIsTrue The boolean value that set the pin
   * as output if argument is `true`, and input when `false` is passed.
   */
  void setPinMode(pin_id_data_type outputPinId, bool outputIsTrue) override;

  /**
   * @brief Waits until a specified time in microseconds.
   * @param timeUs The time in microseconds until to return.
   */
  void waitUntilTimeUs(time_data_type) override;

  // TODO(taiocean1213):
  // void setEventAtTimeUs(time_data_type, void*(void)) override;

  /**
   * @brief Waits for a specified number of microseconds.
   * @param microseconds The number of microseconds to wait.
   */
  void waitMicroseconds(time_data_type) override;

  /**
   * @brief Reads the voltage.
   * @return The read voltage.
   */
  voltage_data_type readVoltage(pin_id_data_type) override;

  /**
   * @brief Sets the voltage.
   * @param voltage The voltage to set.
   */
  void writeVoltage(pin_id_data_type, voltage_data_type) override;

 private:
  int analogResolutionValue{};
  int baudRate{};
  voltage_data_type maxOutputVoltage;
  voltage_data_type minOutputVoltage;
};

#endif