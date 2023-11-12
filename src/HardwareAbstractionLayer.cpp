
#include "HardwareAbstractionLayer.h"

#include <Arduino.h>

/**
 * @brief Constructors that configures the hardware input and output
 *
 * @param analogResolutionValue The number of quantized level is
 * set to `2 ^ (analogResolutionValue)`.
 * @param baudRate The baud rate that is set for communication via
 * the serial port.
 *
 * @tparam voltage_data_type The type of the voltage data.
 * @tparam time_data_type The type of the time data.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
HardwareAbstractionLayer<voltage_data_type, time_data_type, pin_id_data_type>::
    HardwareAbstractionLayer(int analogResolutionValue, int baudRate) {
  this->analogResolutionValue = analogResolutionValue;
  this->baudRate = baudRate;

  // Begin serial communication at `baudRate` baud rate for debugging purposes.
  if (baudRate != 0) {
    Serial.begin(baudRate);
  }

  // Set the analog output and input resolution to digitalResolutionLevel bit
  // (`2 ^ analogResolutionValue` levels).
  analogWriteResolution(analogResolutionValue);
  analogReadResolution(analogResolutionValue);
}

/**
 * @brief Gets the current time in microseconds.
 * @return The current time in microseconds.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
time_data_type HardwareAbstractionLayer<voltage_data_type, time_data_type,
                                        pin_id_data_type>::getCurrentTimeUs() {
  return micros();
}

/**
 * @brief Configures a pin t either output or input mode.
 *
 *
 * @param outputPinId The ID of the pin that needs to be configured.
 * @param outputIsTrue The boolean value that set the pin
 * as output if argument is `true`, and input when `false` is passed.
 *
 * @tparam voltage_data_type The type of the voltage data.
 * @tparam time_data_type The type of the time data.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void HardwareAbstractionLayer<voltage_data_type, time_data_type,
                              pin_id_data_type>::setPinMode(pin_id_data_type
                                                                outputPinId,
                                                            bool outputIsTrue) {
  // if outputIsTrue == true, the set pin with outputPinId
  // as OUTPUT, else set it to input
  pinMode(outputPinId, outputIsTrue ? OUTPUT : INPUT);
}

/**
 * @brief Waits until a specified time in microseconds.
 *
 * This function uses the Arduino micros() function to pause the execution of
 * the program until tje specified microseconds.
 *
 * @tparam voltage_data_type The type of the voltage data.
 * @tparam time_data_type The type of the time data.
 * @param timeUs The time in microseconds to wait.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void HardwareAbstractionLayer<voltage_data_type, time_data_type,
                              pin_id_data_type>::waitUntilTimeUs(time_data_type
                                                                     timeUs) {
  /**
   * @brief Gets the current time in microseconds and stores it in startTime.
   */
  unsigned long const startTime = micros();

  /**
   * @brief Loops until the difference between the current time and startTime is
   * greater than or equal to timeUs. This effectively makes the function wait
   * until the specified time has passed.
   */
  while ((micros() - startTime) < timeUs) {
    // Do nothing, just wait.
  }
}

// /**
//  * @brief Waits until a specified time in microseconds.
//  *
//  * This function uses the Arduino `attachInterrupt()` timer to trigger an
//  event.
//  *
//  * @tparam voltage_data_type The type of the voltage data.
//  * @tparam time_data_type The type of the time data.
//  * @param triggerTimeUs The time in microseconds to trigger the event.
//  */
// template <class voltage_data_type, class time_data_type, class
// pin_id_data_type> void HardwareAbstractionLayer<voltage_data_type,
// time_data_type, pin_id_data_type>::setEventAtTimeUs(time_data_type
// triggerTimeUs, void* (*functionForInterrupt)(void)){

//    // Convert microseconds to milliseconds
//    unsigned long triggerTimeMs = triggerTimeUs / 1000;

//    // Use the attachInterrupt function to set an interrupt
//    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN),
//    functionForInterrupt, CHANGE);

//    // Use the delay function to wait for the specified amount of time
//    delay(triggerTimeMs);

// }

/**
 * @brief Waits for a specified time in microseconds.
 *
 * This function uses the Arduino micros() function to pause the execution of
 * the program for a specified number of microseconds.
 *
 * @tparam voltage_data_type The type of the voltage data.
 * @tparam time_data_type The type of the time data.
 * @param timeUs The time in microseconds to wait.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void HardwareAbstractionLayer<voltage_data_type, time_data_type,
                              pin_id_data_type>::waitMicroseconds(time_data_type
                                                                      timeUs) {
  /**
   * @brief Delay for timeUs based on the parameter.
   */
  delayMicroseconds(timeUs);
}

/**
 * @brief Reads the voltage from the specified pin
 *
 * This function first reads the voltage represented by a quantized level,
 * and converts the quantized level to the actual voltage.
 *
 * @tparam voltage_data_type The type of the voltage data.
 * @tparam time_data_type The type of the time data.
 * @tparam pin_id_data_type The id of the pin
 * @param inputPinId The id of the input pin from which to read the voltage
 * @return The voltage read from the specified pin
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
auto HardwareAbstractionLayer<voltage_data_type, time_data_type,
                              pin_id_data_type>::readVoltage(pin_id_data_type
                                                                 inputPinId)
    -> voltage_data_type {
  // Read the quantized level from the specified pin
  int quantized_level = analogRead(inputPinId);

  // Convert the quantized level to the actual voltage
  // The formula is derived from the information in
  // https://en.wikipedia.org/wiki/Quantization_(signal_processing)
  double voltage_double = quantized_level * this->maxOutputVoltage /
                          pow(2.0, (double)(this->analogResolutionValue));

  // Convert the voltage to the voltage_data_type
  auto voltage = static_cast<voltage_data_type>(voltage_double);

  // Return the voltage
  return voltage;
}

/**
 * @brief Writes the voltage to the specified pin
 *
 * This function converts the voltage to the quantized level based
 * on `analogResolutionValue` set in the constructor and outputs the voltage
 *
 * @tparam voltage_data_type The type of the voltage data.
 * @tparam time_data_type The type of the time data.
 * @tparam pin_id_data_type The id of the pin
 * @param outputPinId The id of the output pin to which to write the voltage
 * @param outputVoltage The voltage to write to the specified pin
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void HardwareAbstractionLayer<
    voltage_data_type, time_data_type,
    pin_id_data_type>::writeVoltage(pin_id_data_type outputPinId,
                                    voltage_data_type outputVoltage) {
  // Convert the output voltage to the quantized level
  // The formula is derived from the information in
  // https://link.springer.com/chapter/10.1007/978-3-030-88439-0_7
  double outputVoltage_double = static_cast<double>(outputVoltage);
  int quantized_level =
      (int)((outputVoltage_double - this->minOutputVoltage) *
            pow(2.0, (double)(this->analogResolutionValue)) /
            (this->maxOutputVoltage - this->minOutputVoltage));

  if (outputVoltage_double == this->maxOutputVoltage) {
    digitalWrite(outputPinId, HIGH);
    return;
  }

  if (outputVoltage_double == this->minOutputVoltage) {
    digitalWrite(outputPinId, LOW);
    return;
  }

  // Output the quantized level to the specified pin
  analogWrite(outputPinId, quantized_level);
}
