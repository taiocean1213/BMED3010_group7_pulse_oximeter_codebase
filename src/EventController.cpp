#include "EventController.h"

#include <map>
#include <vector>

#include "Display.h"
#include "EventController.h"
#include "FastFourierTransform.h"
#include "Filter.h"
#include "HardwareAbstractionLayer.h"
#include "HeartRateCalculator.h"
#include "PPGSignalHardwareController.h"
#include "SignalHistory.h"
#include "SpO2Calculator.h"

/**
 * @brief Constructor for the EventController class.
 *
 * This constructor initializes the HardwareAbstractionLayer,
 * PPGSignalHardwareController, Display, and SignalHistory classes.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
EventController<voltage_data_type, time_data_type,
                pin_id_data_type>::EventController() {
  // initialize the variables containing the device settings
  int analogResolutionValue = 12;
  int baudRate = 38400;
  voltage_data_type minOutputVoltage = 0;
  voltage_data_type maxOutputVoltage = 3.3;
  std::vector<std::pair<voltage_data_type, voltage_data_type>> passbands = {
      {1, 2}, {3, 4}};
  std::vector<std::pair<voltage_data_type, voltage_data_type>> stopbands = {
      {5, 6}, {7, 8}};
  voltage_data_type samplingFrequency = 40;
  voltage_data_type signalHistoryContainerElemenmts = 50;

  // Initialize the objects using new keyword
  this->helperClassInstance = {
      .hardwareLayerPtr = new HardwareAbstractionLayer<
          voltage_data_type, time_data_type, pin_id_data_type>(
          analogResolutionValue, baudRate, minOutputVoltage, maxOutputVoltage),

      .ppgSignalControllerPtr =
          new PPGSignalHardwareController<voltage_data_type, time_data_type,
                                          pin_id_data_type>(
              this->helperClassInstance.hardwareLayerPtr),

      .displayPtr = new Display<voltage_data_type>(),

      .signalHistoryPtr =
          new SignalHistory<voltage_data_type>(signalHistoryContainerElemenmts),

      .fftPtr = new FastFourierTransform<voltage_data_type>(),

      .filterPtr = new Filter<voltage_data_type, voltage_data_type>(
          passbands, stopbands, samplingFrequency,
          this->helperClassInstance.fftPtr),

      .spO2CalculatorPtr = new SpO2Calculator<voltage_data_type>(),

      .heartRateCalculatorPtr = new HeartRateCalculator<voltage_data_type>()

  };

  this->helperClassInstance.displayPtr->begin();
  this->helperClassInstance.signalHistoryPtr->reset();

  // Set up the deviceStatus of class
  deviceStatus = {.redLedVoltage = 0,
                  .infraRedLedVoltage = 0,
                  .rawPhotodiodeVoltage = 0,
                  .eventSequenceStartTime = 0,
                  .eventSequenceEndTime = 0,
                  .deviceState = RedLedOn};
};

/**
 * @brief Destructor for the EventController class.
 *
 * This destructor deletes the HardwareAbstractionLayer,
 * PPGSignalHardwareController, Display, and SignalHistory classes.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
EventController<voltage_data_type, time_data_type,
                pin_id_data_type>::~EventController() {
  // delete this -> helperClassInstance objects
  delete this->helperClassInstance.hardwareLayerPtr;
  delete this->helperClassInstance.ppgSignalControllerPtr;
  delete this->helperClassInstance.displayPtr;
  delete this->helperClassInstance.signalHistoryPtr;
  delete this->helperClassInstance.fftPtr;
  delete this->helperClassInstance.filterPtr;
  delete this->helperClassInstance.spO2CalculatorPtr;
  delete this->helperClassInstance.heartRateCalculatorPtr;
};

/**
 * @brief LoopOnce method for implementing the logic for the main loop of the
 * event controller.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void EventController<voltage_data_type, time_data_type,
                     pin_id_data_type>::loopOnce() {
  DeviceStatus* deviceStatusStructPtr = &deviceStatus;

  // Check for the state of the program
  DeviceState currentState = deviceStatusStructPtr->deviceState;

  // Branch off to check for the corresponding action to take
  switch (currentState) {
    case RedLedOn:
      // Code to execute when RedLedOn
      break;
    case InfraRedLedOn:
      // Code to execute when InfraRedLedOn
      break;
    case PhotoDetectorReading:
      // Code to execute when PhotoDetectorReading
      break;
    case UiIsUpdating:
      // Code to execute when UiIsUpdating
      break;
    case SignalIsProcessing:
      // Code to execute when SignalIsProcessing
      break;
    case DeviceIdling:
      // Code to execute when DeviceIdling
      break;
    case GettingEventSequenceStartTime:
      // Code to execute when GettingEventSequenceStartTime
      break;
    case GettingEventSequenceEndTime:
      // Code to execute when GettingEventSequenceEndTime
      break;
    default:
      // Code to execute when 'state' is not any of the above cases
      break;
  }

  // Decide what to do next

  /*
// Check which LED is on from the class
bool isRedLedOn = ppgSignalControllerPtr->getRedLED();
bool isInfraRedLedOn = ppgSignalControllerPtr->getInfraRedLED();

// Change the other LED to be turned on
if (isRedLedOn) {
ppgSignalControllerPtr->setInfraRedLED(voltage_data_type());
} else if (isInfraRedLedOn) {
ppgSignalControllerPtr->setRedLED(voltage_data_type());
}

// Sample the photodiode voltage after some waiting time for the LED to warm
// up (200 microseconds)
voltage_data_type photodiodeVoltage =
ppgSignalControllerPtr->getPhotoDiodeVoltage(200);

// Store the signal to the corresponding SignalHistory class
signalHistoryPtr->put(photodiodeVoltage);

// Check if the time since the last timestamp was set from 1/60 seconds ago
if (!((signalHistoryPtr->getEntryPointIndex() == 1 / 60))) {
return;
}

// Apply the filter to the signal
std::vector<voltage_data_type> filteredSignal =
filterPtr->filter(fftPtr->fastFourierTransform(
signalHistoryPtr->get(nthSample)));

// Update the filteredSignal Class and update to the class method of `Display`
displayPtr->updatePPGWave(filteredSignal.data(),
                filteredSignal.size(), min_ppg_value,
                max_ppg_value);

// Perform heartBeatRate and SP02 computation if there is a new heart beat
// detected
voltage_data_type spo2Value =
spO2CalculatorPtr->calculate(filteredSignal);
voltage_data_type hrValue =
heartRateCalculatorPtr->calculate(filteredSignal);

// Update the Display class by passing the HBR, SPO2 filtered SignalPoint
displayPtr->updateSpO2(spo2Value);
displayPtr->updateHBR(hrValue);
*/
};
