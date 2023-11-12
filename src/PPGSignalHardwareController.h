#ifndef PPGSIGNALHARDWARECONTROLLER_H
#define PPGSIGNALHARDWARECONTROLLER_H

#include "hardware_driver_apis/HardwareAbstractionLayerInterface.h"
#include "ppg_signal_io/PPGSignalHardwareControllerInterface.h"

/**
 * @brief PPGSignalHardwareController class.
 *
 * This class is responsible for controlling the hardware related to the PPG
 * signal. It uses the HardwareAbstractionLayerInterface to interact with the
 * hardware.
 *
 * @tparam voltage_data_type The data type used for voltage values.
 * @tparam time_data_type The data type used for time values.
 * @tparam pin_id_data_type The data type used for pin IDs.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class PPGSignalHardwareController
    : public PPGSignalHardwareControllerInterface<
          voltage_data_type, time_data_type, pin_id_data_type> {
 private:
  /**
   * @brief Pointer to the HardwareAbstractionLayerInterface object.
   *
   * This member variable is used to interact with the hardware.
   */
  HardwareAbstractionLayerInterface<voltage_data_type, time_data_type,
                                    pin_id_data_type>* hardwareLayer;

 public:
  /**
   * @brief Constructor of the PPGSignalHardwareController class.
   *
   * @param hardwareLayer Pointer to the HardwareAbstractionLayerInterface
   * object.
   */
  PPGSignalHardwareController(
      HardwareAbstractionLayerInterface<voltage_data_type, time_data_type,
                                        pin_id_data_type>* hardwareLayer);

  /**
   * @brief Gets the current time in microseconds.
   *
   * @return The current time in microseconds.
   */
  time_data_type getCurrentTimeUs() override;

  /**
   * @brief Sets the voltage of the red LED.
   *
   * @param ledVoltage The voltage to set the red LED to.
   */
  void setRedLED(voltage_data_type ledVoltage) override;

  /**
   * @brief Sets the voltage of the infrared LED.
   *
   * @param ledVoltage The voltage to set the infrared LED to.
   */
  void setInfraRedLED(voltage_data_type ledVoltage) override;

  /**
   * @brief Gets the voltage of the photo diode.
   *
   * @param photoDiodeWarmupTimeMs The time in milliseconds to warm up the
   * photodiode.
   * @return The voltage of the photo diode.
   */
  voltage_data_type getPhotoDiodeVoltage(
      time_data_type photoDiodeWarmupTimeMs) override;
};

// Explicit instantiation
template class PPGSignalHardwareController<int, unsigned long, int>;

#endif /* PPGSIGNALHARDWARECONTROLLER_H */
