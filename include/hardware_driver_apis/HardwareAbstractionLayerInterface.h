#ifndef HARDWAREABSTRACTIONLAYERINTERFACE_H
#define HARDWAREABSTRACTIONLAYERINTERFACE_H

/**
 * @interface HardwareAbstractionLayerInterface
 * @brief Abstract base class for communicating with hardware.
 *
 * This class provides an interface for communicating with hardware. It contains
 * methods for getting the current time, setting pin modes, waiting for a
 * specified time, reading and writing voltages.
 *
 * @tparam voltage_data_type The type of the voltage data.
 * @tparam time_data_type The type of the time data.
 * @tparam pin_id_data_type The type of the pin ID data.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class HardwareAbstractionLayerInterface {
 public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~HardwareAbstractionLayerInterface() {}

  /**
   * @brief setup that configures the hardware input and output
   *
   * @param analogResolutionValue The number of quantized level is
   * set to `2 ^ (analogResolutionValue)`.
   * @param baudRate The baud rate that is set for communication via
   * the serial port.
   */
  virtual void setup(int analogResolutionValue, int baudRate,
                     voltage_data_type minOutputVoltage,
                     voltage_data_type maxOutputVoltage) = 0;

  /**
   * @brief Gets the current time in microseconds.
   * @return The current time in microseconds.
   */
  virtual time_data_type getCurrentTimeUs() = 0;

  /**
   * @brief Configures a pin either output or input mode.
   *
   * @param outputPinId The ID of the pin that needs to be configured.
   * @param outputIsTrue The boolean value that set the pin
   * as output if argument is `true`, and input when `false` is passed.
   */
  virtual void setPinMode(pin_id_data_type outputPinId, bool outputIsTrue) = 0;

  /**
   * @brief Waits until a specified time in microseconds.
   * @param timeUs The time in microseconds to wait.
   */
  virtual void waitUntilTimeUs(time_data_type timeUs) = 0;

  /**
   * @brief Waits for a specified time in microseconds.
   * @param timeUs The time in microseconds to wait.
   */
  virtual void waitMicroseconds(time_data_type timeUs) = 0;

  /**
   * @brief Reads the voltage from the specified pin.
   * @param inputPinId The id of the input pin from which to read the voltage
   * @return The voltage read from the specified pin
   */
  virtual voltage_data_type readVoltage(pin_id_data_type inputPinId) = 0;

  /**
   * @brief Writes the voltage to the specified pin.
   * @param outputPinId The id of the output pin to which to write the voltage
   * @param outputVoltage The voltage to write to the specified pin
   */
  virtual void writeVoltage(pin_id_data_type outputPinId,
                            voltage_data_type outputVoltage) = 0;
};

#endif