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
  this->deviceSettings = {
      12,                // analogResolutionValue
      38400,             // baudRate
      0,                 // minOutputVoltage
      3.3,               // maxOutputVoltage
      {{1, 2}, {3, 4}},  // passbandsHz
      {{5, 6}, {7, 8}},  // stopbandsHz
      40,                // samplingFrequencyHz
      50                 // signalHistoryElementsCount
  };

  // Initialize the objects using new keyword
  this->helperClassInstance = {
      .hardwareLayerPtr = new HardwareAbstractionLayer<
          voltage_data_type, time_data_type, pin_id_data_type>(
          this->deviceSettings.analogResolutionValue,
          this->deviceSettings.baudRate, this->deviceSettings.minOutputVoltage,
          this->deviceSettings.maxOutputVoltage),

      .ppgSignalControllerPtr =
          new PPGSignalHardwareController<voltage_data_type, time_data_type,
                                          pin_id_data_type>(
              this->helperClassInstance.hardwareLayerPtr),

      .displayPtr = new Display<voltage_data_type>(),

      .signalHistoryPtr = new SignalHistory<voltage_data_type>(
          this->deviceSettings.signalHistoryElementsCount),

      .fftPtr = new FastFourierTransform<voltage_data_type>(),

      .filterPtr = new Filter<voltage_data_type, voltage_data_type>(
          this->deviceSettings.passbandsHz, this->deviceSettings.stopbandsHz,
          this->deviceSettings.samplingFrequencyHz,
          this->helperClassInstance.fftPtr),

      .spO2CalculatorPtr = new SpO2Calculator<voltage_data_type>(),

      .heartRateCalculatorPtr = new HeartRateCalculator<voltage_data_type>()

  };

  this->helperClassInstance.displayPtr->begin();
  this->helperClassInstance.signalHistoryPtr->reset();

  // Set up the deviceStatus of class
  this->deviceStatus = {.redLedVoltage = 0,
                        .infraRedLedVoltage = 0,
                        .rawPhotodiodeVoltage = 0,
                        .eventSequenceStartTimeUs = 0,
                        .eventSequenceEndTimeUs = 0,
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

  // Branch off to check for creating flags for the corresponding action to take
  switch (currentState) {
    case RedLedOn:
      // Code to execute when RedLedOn
      // FIXME Boilerplate code at line below:
      this->deviceStatus = {.redLedVoltage = 0,
                            .infraRedLedVoltage = 0,
                            .rawPhotodiodeVoltage = 0,
                            .eventSequenceStartTimeUs = 0,
                            .eventSequenceEndTimeUs = 0,
                            .deviceState = RedLedOn};
      break;
    case InfraRedLedOn:
      // Code to execute when InfraRedLedOn
      // FIXME Boilerplate code at line below:
      this->deviceStatus = {.redLedVoltage = 0,
                            .infraRedLedVoltage = 0,
                            .rawPhotodiodeVoltage = 0,
                            .eventSequenceStartTimeUs = 0,
                            .eventSequenceEndTimeUs = 0,
                            .deviceState = RedLedOn};
      break;
    case PhotoDetectorReading:
      // Code to execute when PhotoDetectorReading
      // FIXME Boilerplate code at line below:
      this->deviceStatus = {.redLedVoltage = 0,
                            .infraRedLedVoltage = 0,
                            .rawPhotodiodeVoltage = 0,
                            .eventSequenceStartTimeUs = 0,
                            .eventSequenceEndTimeUs = 0,
                            .deviceState = RedLedOn};
      break;
    case UiIsUpdating:
      // Code to execute when UiIsUpdating
      // FIXME Boilerplate code at line below:
      this->deviceStatus = {.redLedVoltage = 0,
                            .infraRedLedVoltage = 0,
                            .rawPhotodiodeVoltage = 0,
                            .eventSequenceStartTimeUs = 0,
                            .eventSequenceEndTimeUs = 0,
                            .deviceState = RedLedOn};
      break;
    case SignalIsProcessing:
      // Code to execute when SignalIsProcessing
      // FIXME Boilerplate code at line below:
      this->deviceStatus = {.redLedVoltage = 0,
                            .infraRedLedVoltage = 0,
                            .rawPhotodiodeVoltage = 0,
                            .eventSequenceStartTimeUs = 0,
                            .eventSequenceEndTimeUs = 0,
                            .deviceState = RedLedOn};
      break;
    case DeviceIdling:
      // Code to execute when DeviceIdling
      // FIXME Boilerplate code at line below:
      this->deviceStatus = {.redLedVoltage = 0,
                            .infraRedLedVoltage = 0,
                            .rawPhotodiodeVoltage = 0,
                            .eventSequenceStartTimeUs = 0,
                            .eventSequenceEndTimeUs = 0,
                            .deviceState = RedLedOn};
      break;
    case GettingEventSequenceStartTime:
      // Code to execute when GettingEventSequenceStartTime
      this->deviceStatus.eventSequenceStartTimeUs =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs();

      break;
    case GettingEventSequenceEndTime:
      // Code to execute when GettingEventSequenceEndTime
      this->deviceStatus.eventSequenceEndTimeUs =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs();

      break;
    default:
      // Code to execute when 'state' is not any of the above cases
      break;
  }

  // Decide what is the next state

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
