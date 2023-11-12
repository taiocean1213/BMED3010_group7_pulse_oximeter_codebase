/**
 * @interface PPGSignalHardwareControllerInterface
 * @brief Abstract base class for controlling LEDs.
 */

#ifndef PPG_SIGNAL_IO_PPGSIGNALHARDWARECONTROLLERINTERFACE_H
#define PPG_SIGNAL_IO_PPGSIGNALHARDWARECONTROLLERINTERFACE_H


template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class PPGSignalHardwareControllerInterface {
 public:
  virtual time_data_type getCurrentTimeUs();
  virtual void setRedLED(voltage_data_type ledVoltage);
  virtual void setInfraRedLED(voltage_data_type ledVoltage);
  virtual voltage_data_type getPhotoDiodeVoltage(
      time_data_type photoDiodeWarmupTimeMs = 200);
};

#endif