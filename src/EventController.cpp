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
  // initialize the device settings
  this->deviceSettings = {.analogResolutionValue = 12,
                          .baudRate = 38400,
                          .minOutputVoltage = 0,
                          .maxOutputVoltage = 3.3,
                          .passbandsHz = {{1, 2}, {3, 4}},
                          .stopbandsHz = {{5, 6}, {7, 8}},
                          .samplingFrequencyHz = 40,
                          .signalHistoryElementsCount = 50,
                          .photoDiodeWarmupTimeUs = 200};

  // Set up the deviceStatus of class for data recording
  this->deviceStatus = {
      .redLedVoltage = 0, .infraRedLedVoltage = 0, .deviceState = RedLedOn};

  for (int i = 0; i < DeviceStateTotal; ++i)
    this->deviceStatus.statesCompleted[i] = 0;

  // Set up the deviceStatus of class for data recording
  this->deviceMemory = {
      .rawPhotodiodeVoltage = 0,
      .eventSequenceStartTimeUs = 0,
      .eventSequenceEndTimeUs = 0,
      .rawRedPPGSignalHistoryPtr = new SignalHistory<voltage_data_type>(
          this->deviceSettings.signalHistoryElementsCount),
      .filteredRedPPGSignalHistoryPtr = new SignalHistory<voltage_data_type>(
          this->deviceSettings.signalHistoryElementsCount),
      .rawInfraRedPPGSignalHistoryPtr = new SignalHistory<voltage_data_type>(
          this->deviceSettings.signalHistoryElementsCount),
      .filteredInfraRedPPGSignalHistoryPtr =
          new SignalHistory<voltage_data_type>(
              this->deviceSettings.signalHistoryElementsCount),

      .spO2Value = 0,
      .heartBeatRateValue = 0,
  };
  this->deviceMemory.rawRedPPGSignalHistoryPtr->reset();
  this->deviceMemory.filteredRedPPGSignalHistoryPtr->reset();
  this->deviceMemory.rawInfraRedPPGSignalHistoryPtr->reset();
  this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr->reset();

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

      .fftPtr = new FastFourierTransform<voltage_data_type>(),

      .filterPtr = new Filter<voltage_data_type, voltage_data_type>(
          this->deviceSettings.passbandsHz, this->deviceSettings.stopbandsHz,
          this->deviceSettings.samplingFrequencyHz,
          this->helperClassInstance.fftPtr),

      .spO2CalculatorPtr = new SpO2Calculator<voltage_data_type>(),

      .heartRateCalculatorPtr = new HeartRateCalculator<voltage_data_type>()

  };

  this->helperClassInstance.displayPtr->begin();
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
  delete this->helperClassInstance.fftPtr;
  delete this->helperClassInstance.filterPtr;
  delete this->helperClassInstance.spO2CalculatorPtr;
  delete this->helperClassInstance.heartRateCalculatorPtr;

  // delete this->deviceMemory objects
  delete this->deviceMemory.rawRedPPGSignalHistoryPtr;
  delete this->deviceMemory.filteredRedPPGSignalHistoryPtr;
  delete this->deviceMemory.rawInfraRedPPGSignalHistoryPtr;
  delete this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr;
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

  // Branch off to check for creating flags for the corresponding action to
  // take. Input for the current state
  switch (currentState) {
    case RedLedOn:
      // Code to execute when RedLedOn.
      break;
    case InfraRedLedOn:
      // Change the LED status based on above modification
      break;
    case PhotoDetectorReading:
      // Code to execute when PhotoDetectorReading.
      this->deviceMemory.rawPhotodiodeVoltage =
          this->helperClassInstance.ppgSignalControllerPtr
              ->getPhotoDiodeVoltage(
                  this->deviceSettings.photoDiodeWarmupTimeUs);
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
    case EventSequenceStarting:
      // Code to execute when EventSequenceStarting
      this->deviceMemory.eventSequenceStartTimeUs =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs();

      break;
    case EventSequenceEnding:
      // Code to execute when EventSequenceEnding
      this->deviceMemory.eventSequenceEndTimeUs =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs();

      break;
    default:
      // Code to execute when 'state' is not any of the above cases
      break;
  }

  // Computing for the actions current state.
  switch (currentState) {
    case RedLedOn:
      // Code to execute when RedLedOn.
      this->deviceStatus.redLedVoltage = this->deviceSettings.maxOutputVoltage;
      this->deviceStatus.infraRedLedVoltage =
          this->deviceSettings.minOutputVoltage;
      break;
    case InfraRedLedOn:
      this->deviceStatus.redLedVoltage = this->deviceSettings.minOutputVoltage;
      this->deviceStatus.infraRedLedVoltage =
          this->deviceSettings.maxOutputVoltage;
      break;
    case PhotoDetectorReading:
      // Code to execute when PhotoDetectorReading.
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
    case EventSequenceStarting:
      // Code to execute when EventSequenceStarting
      break;
    case EventSequenceEnding:
      // Code to execute when EventSequenceEnding
      break;
    default:
      // Code to execute when 'state' is not any of the above cases
      break;
  }

  // Performing actions for the current state.
  switch (currentState) {
    case RedLedOn:
      // Code to execute when RedLedOn.
      this->helperClassInstance.ppgSignalControllerPtr->setRedLED(
          this->deviceStatus.redLedVoltage);
      this->helperClassInstance.ppgSignalControllerPtr->setInfraRedLED(
          this->deviceStatus.infraRedLedVoltage);
      break;
    case InfraRedLedOn:
      // Change the LED status based on above modification
      this->helperClassInstance.ppgSignalControllerPtr->setRedLED(
          this->deviceStatus.redLedVoltage);
      this->helperClassInstance.ppgSignalControllerPtr->setInfraRedLED(
          this->deviceStatus.infraRedLedVoltage);
    case PhotoDetectorReading:
      // Code to execute when PhotoDetectorReading.
      if (this->deviceStatus.statesCompleted[RedLedOn] >
          this->deviceStatus.statesCompleted[InfraRedLedOn]) {
        this->deviceMemory.rawRedPPGSignalHistoryPtr->put(
            this->deviceMemory.rawPhotodiodeVoltage);
      } else if (this->deviceStatus.statesCompleted[RedLedOn] ==
                 this->deviceStatus.statesCompleted[InfraRedLedOn]) {
        this->deviceMemory.rawInfraRedPPGSignalHistoryPtr->put(
            this->deviceMemory.rawPhotodiodeVoltage);
      } else {
        // assert an error.
      }
      break;
    case UiIsUpdating:
      // TODO Code to execute when UiIsUpdating
      /*
      this->helperClassInstance.displayPtr->updateSpO2(
          values_data_type spo2_value);
      this->helperClassInstance.displayPtr->updateHBR(
          values_data_type spo2_value);
      this->helperClassInstance.displayPtr->updatePPGWave(
          values_data_type ppg_values[], int num_values,
          values_data_type min_ppg_value, values_data_type max_ppg_value);
      */
      break;
    case SignalIsProcessing:
      //  TODO Code to execute when SignalIsProcessing
      this->helperClassInstance.filterPtr->process(
          this->deviceMemory.rawRedPPGSignalHistoryPtr,
          this->deviceMemory.filteredRedPPGSignalHistoryPtr);
      this->helperClassInstance.filterPtr->process(
          this->deviceMemory.rawInfraRedPPGSignalHistoryPtr,
          this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr);
      // Calculate the biomedical metrics
      this->deviceMemory.spO2Value =
          this->helperClassInstance.spO2CalculatorPtr->calculate(
              this->deviceMemory.filteredRedPPGSignalHistoryPtr,
              this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr);
      this->deviceMemory.heartBeatRateValue =
          this->helperClassInstance.heartRateCalculatorPtr->calculate(
              this->deviceMemory.filteredRedPPGSignalHistoryPtr,
              this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr);
      break;
    case DeviceIdling:
      // Code to execute when DeviceIdling
      break;
    case EventSequenceStarting:
      // Code to execute when EventSequenceStarting
      for (int i = 0; i < DeviceStateTotal; ++i)
        this->deviceStatus.statesCompleted[i] = 0;
      break;
    case EventSequenceEnding:
      // Code to execute when EventSequenceEnding
      break;
    default:
      // Code to execute when 'state' is not any of the above cases
      break;
  }
  ++(this->deviceStatus.statesCompleted[currentState]);

  // Calculating and deciding what the next state is.
  switch (currentState) {
    case RedLedOn:
      // Code to execute when RedLedOn.
      break;
    case InfraRedLedOn:
      // Change the LED status based on above modification
      break;
    case PhotoDetectorReading:
      // Code to execute when PhotoDetectorReading.
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
    case EventSequenceStarting:
      // Code to execute when EventSequenceStarting
      break;
    case EventSequenceEnding:
      // Code to execute when EventSequenceEnding
      break;
    default:
      // Code to execute when 'state' is not any of the above cases
      break;
  }
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
rawRedPPGSignalHistoryPtr->put(photodiodeVoltage);

// Check if the time since the last timestamp was set from 1/60 seconds ago
if (!((rawRedPPGSignalHistoryPtr->getEntryPointIndex() == 1 / 60))) {
return;
}

// Apply the filter to the signal
std::vector<voltage_data_type> filteredSignal =
filterPtr->filter(fftPtr->fastFourierTransform(
rawRedPPGSignalHistoryPtr->get(nthSample)));

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
