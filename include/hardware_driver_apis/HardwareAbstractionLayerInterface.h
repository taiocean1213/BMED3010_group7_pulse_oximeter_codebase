
/**
 * @interface HardwareControlInterface
 * @brief Abstract base class for communicating with hardware.
 */

#ifndef HARDWAREABSTRACTIONLAYERINTERFACE_H
#define HARDWAREABSTRACTIONLAYERINTERFACE_H

template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class HardwareAbstractionLayerInterface {
 public:
  virtual ~HardwareAbstractionLayerInterface() {}
  virtual time_data_type getCurrentTimeUs() = 0;
  virtual void setPinMode(pin_id_data_type outputPinId, bool outputIsTrue) = 0;
  virtual time_data_type waitUntilTimeUs(time_data_type) = 0;
  virtual void waitMicroseconds(time_data_type) = 0;
  virtual voltage_data_type readVoltage(pin_id_data_type) = 0;
  virtual void writeVoltage(pin_id_data_type, voltage_data_type) = 0;
};

#endif