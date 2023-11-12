#include "PPGSignalHardwareController.h"

#include <Arduino.h>

#include "hardware_driver_apis/HardwareAbstractionLayerInterface.h"

#define PHOTODIODE_PIN A0
#define RED_SIGNAL_PIN DAC0
#define INFRARED_SIGNAL_PIN DAC1


/**
 * @class PPGSignalHardwareController
 * @brief A class that controls the hardware for PPG signals.
 *
 * This class is a template class that takes three parameters:
 * voltage_data_type, time_data_type, and pin_id_data_type. It provides
 * methods to get the current time, set the voltage of the red and infrared
 * LEDs, and get the voltage of the photo diode.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
PPGSignalHardwareController<voltage_data_type, time_data_type,
                            pin_id_data_type>::
    PPGSignalHardwareController(
        HardwareAbstractionLayerInterface<voltage_data_type, time_data_type,
                                          pin_id_data_type>* hardwareLayer)
    : hardwareLayer(hardwareLayer) {}

/**
 * @brief Gets the current time in microseconds.
 * @return The current time in microseconds.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
auto PPGSignalHardwareController<voltage_data_type, time_data_type,
                                 pin_id_data_type>::getCurrentTimeUs()
    -> time_data_type {
  return hardwareLayer->getCurrentTimeUs();
}

/**
 * @brief Sets the voltage of the red LED.
 * @param ledVoltage The voltage to set for the red LED.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void PPGSignalHardwareController<voltage_data_type, time_data_type,
                                 pin_id_data_type>::setRedLED(voltage_data_type
                                                                  ledVoltage) {
  hardwareLayer->writeVoltage(INFRARED_SIGNAL_PIN, ledVoltage);
}

/**
 * @brief Sets the voltage of the infrared LED.
 * @param ledVoltage The voltage to set for the infrared LED.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void PPGSignalHardwareController<
    voltage_data_type, time_data_type,
    pin_id_data_type>::setInfraRedLED(voltage_data_type ledVoltage) {
  hardwareLayer->writeVoltage(RED_SIGNAL_PIN, ledVoltage);
}

/**
 * @brief Gets the voltage of the photo diode.
 * @param photoDiodeWarmupTimeMs The time to wait for the photo diode to warm up
 * before reading the voltage.
 * @return The voltage of the photo diode.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
auto PPGSignalHardwareController<voltage_data_type, time_data_type,
                                 pin_id_data_type>::
    getPhotoDiodeVoltage(time_data_type photoDiodeWarmupTimeMs)
        -> voltage_data_type {
  hardwareLayer->waitMicroseconds(photoDiodeWarmupTimeMs);
  return hardwareLayer->readVoltage(PHOTODIODE_PIN);
}
