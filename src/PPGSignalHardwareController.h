#ifndef PPGSIGNALHARDWARECONTROLLER_H
#define PPGSIGNALHARDWARECONTROLLER_H

#include <Arduino.h>

#include "ppg_signal_io/PPGSignalHardwareControllerInterface.h"

/**
 * @class PPGSignalHardwareController
 * @brief Abstract base class for controlling LEDs.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class PPGSignalHardwareController
    : public PPGSignalHardwareControllerInterface<
          voltage_data_type, time_data_type, pin_id_data_type> {
 public:
  /**
   * @brief Gets the current time in microseconds.
   * @return The current time in microseconds.
   */
  time_data_type getCurrentTimeUs() override;

  /**
   * @brief Sets the voltage of the red LED.
   * @param ledVoltage The voltage to set the red LED to.
   */
  void setRedLED(voltage_data_type ledVoltage) override;

  /**
   * @brief Sets the voltage of the infrared LED.
   * @param ledVoltage The voltage to set the infrared LED to.
   */
  void setInfraRedLED(voltage_data_type ledVoltage) override;

  /**
   * @brief Gets the voltage of the photo diode.
   * @param photoDiodeWarmupTimeMs The time in milliseconds to warm up the photo
   * diode.
   * @return The voltage of the photo diode.
   */
  voltage_data_type getPhotoDiodeVoltage(
      time_data_type photoDiodeWarmupTimeMs = 200) override;
};

#endif