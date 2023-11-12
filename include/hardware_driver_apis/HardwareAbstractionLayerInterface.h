
/**
 * @interface HardwareControlInterface
 * @brief Abstract base class for communicating with hardware.
 */

#ifndef HARDWAREABSTRACTIONLAYERINTERFACE_H
#define HARDWAREABSTRACTIONLAYERINTERFACE_H

template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class HardwareAbstractionLayerInterface {
 public:
  virtual time_data_type getCurrentTimeUs();
  virtual void setPinMode(pin_id_data_type outputPinId, bool outputIsTrue);
  virtual time_data_type waitUntilTimeUs();
  virtual void setEventAtTimeUs(time_data_type, void*(void)) = 0;
  virtual void waitMicroseconds(time_data_type);
  virtual voltage_data_type readVoltage(pin_id_data_type);
  virtual void writeVoltage(pin_id_data_type, voltage_data_type);
};

#endif