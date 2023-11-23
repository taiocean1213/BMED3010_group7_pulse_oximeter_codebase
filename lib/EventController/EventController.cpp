#include "EventController.h"

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
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
EventController<voltage_data_type, time_data_type,
                pin_id_data_type>::EventController() {}

/**
 * @brief setup for the EventController class.
 *
 * This setup method initializes the HardwareAbstractionLayer,
 * PPGSignalHardwareController, Display, and SignalHistory classes.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void EventController<voltage_data_type, time_data_type,
                     pin_id_data_type>::setup() {
  this->deviceSettings = {.analogResolutionValue = 12,
                          .baudRate = 38400,
                          .minOutputVoltage = 0,
                          .maxOutputVoltage = 3.3,
                          .passbandsHz = {{1, 2}, {3, 4}},
                          .stopbandsHz = {{5, 6}, {7, 8}},
                          .samplingPeriodUs = 1000000 / 40,
                          .signalHistoryElementsCount = 50,
                          .photoDiodeWarmupTimeUs = 200,
                          .screenRefreshTimeIntervalUs = 1000000 / 2};
  this->deviceStatus = {
      .redLedVoltage = 0, .infraRedLedVoltage = 0, .deviceState = RedLedOn};
  this->helperClassInstance = {.hardwareLayerPtr = nullptr,
                               .ppgSignalControllerPtr = nullptr,
                               .displayPtr = nullptr,
                               .fftPtr = nullptr,
                               .filterPtr = nullptr,
                               .spO2CalculatorPtr = nullptr,
                               .heartRateCalculatorPtr = nullptr};

  // Initialize all statesCompleted to 0
  for (int i = 0; i < DeviceStateTotal; ++i)
    this->deviceStatus.statesCompleted[i] = 0;

  // Initialize helperClassInstance objects
  this->helperClassInstance.hardwareLayerPtr =
      new HardwareAbstractionLayer<voltage_data_type, time_data_type,
                                   pin_id_data_type>();

  this->helperClassInstance.hardwareLayerPtr->setup(
      this->deviceSettings.analogResolutionValue, this->deviceSettings.baudRate,
      this->deviceSettings.minOutputVoltage,
      this->deviceSettings.maxOutputVoltage);

  this->helperClassInstance.ppgSignalControllerPtr =
      new PPGSignalHardwareController<voltage_data_type, time_data_type,
                                      pin_id_data_type>();

  this->helperClassInstance.ppgSignalControllerPtr->setup(
      this->helperClassInstance.hardwareLayerPtr);

  this->helperClassInstance.displayPtr = new Display<voltage_data_type>();

  this->helperClassInstance.fftPtr =
      new FastFourierTransform<voltage_data_type>();

  this->helperClassInstance.filterPtr =
      new Filter<voltage_data_type, time_data_type>(
          this->deviceSettings.passbandsHz, this->deviceSettings.stopbandsHz,
          this->deviceSettings.samplingPeriodUs,
          this->helperClassInstance.fftPtr);

  this->helperClassInstance.spO2CalculatorPtr =
      new SpO2Calculator<voltage_data_type>();

  this->helperClassInstance.heartRateCalculatorPtr =
      new HeartRateCalculator<voltage_data_type>();

  this->helperClassInstance.displayPtr->begin();

  // Initialize deviceMemory
  this->deviceMemory = {
      .rawPhotodiodeVoltage = 0,
      .eventSequenceStartTimeUs =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs(),
      .eventSequenceEndTimeUs =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs() +
          this->deviceSettings.screenRefreshTimeIntervalUs,
      .lastDisplayUpdateTime = 0,
      .lastFilteredSignalUpdateTime = 0,
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

  // Reset all signal histories
  this->deviceMemory.rawRedPPGSignalHistoryPtr->reset();
  this->deviceMemory.filteredRedPPGSignalHistoryPtr->reset();
  this->deviceMemory.rawInfraRedPPGSignalHistoryPtr->reset();
  this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr->reset();

  /*Serial.begin(38400);
  while (true) {

    ppgSignalControllerPtr->setRedLED(
        this->deviceSettings.maxOutputVoltage);
    this->helperClassInstance.ppgSignalControllerPtr->setRedLED(
        this->deviceSettings.minOutputVoltage);

    Serial.println("successfully intitlized.");
  }*/
};

/**
 * @brief Destructor for the EventController class.
 *
 * This destructor deletes the HardwareAbstractionLayer,
 * PPGSignalHardwareController, Display, and SignalHistory classes.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
EventController<voltage_data_type, time_data_type,
                pin_id_data_type>::~EventController(){
    // Delete helperClassInstance objects
    // delete this->helperClassInstance.hardwareLayerPtr;
    // delete this->helperClassInstance.ppgSignalControllerPtr;
    // delete this->helperClassInstance.displayPtr;
    // delete this->helperClassInstance.fftPtr;
    // delete this->helperClassInstance.filterPtr;
    // delete this->helperClassInstance.spO2CalculatorPtr;
    // delete this->helperClassInstance.heartRateCalculatorPtr;

    // // Delete deviceMemory objects
    // delete this->deviceMemory.rawRedPPGSignalHistoryPtr;
    // delete this->deviceMemory.filteredRedPPGSignalHistoryPtr;
    // delete this->deviceMemory.rawInfraRedPPGSignalHistoryPtr;
    // delete this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr;
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

  // Checking the current state
  this->checkCurrentState(currentState);

  // Performing actions based on the current state
  this->performStateAction(currentState);

  // Updating the state
  this->updateStateEventCount(currentState);

  // Calculating the next state
  DeviceState nextState = this->calculateNextState(currentState);

  // Assigning the nextState to the deviceStatusStructPtr->deviceState
  deviceStatusStructPtr->deviceState = nextState;
};

/**
 * @brief Checks the current state of the program.
 *
 * This method executes different code depending on the current state of the
 * program.
 *
 * @param currentState The current state of the program.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void EventController<voltage_data_type, time_data_type, pin_id_data_type>::
    checkCurrentState(DeviceState currentState) {
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
      this->deviceMemory.lastDisplayUpdateTime =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs();
      break;
    case SignalIsProcessing:
      // Code to execute when SignalIsProcessing
      this->deviceMemory.lastFilteredSignalUpdateTime =
          this->helperClassInstance.ppgSignalControllerPtr->getCurrentTimeUs() +
          this->deviceSettings.screenRefreshTimeIntervalUs / 2;
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
};

/**
 * @brief Performs actions based on the current state of the program.
 *
 * This method executes different code depending on the current state of the
 * program.
 *
 * @param currentState The current state of the program.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void EventController<voltage_data_type, time_data_type, pin_id_data_type>::
    performStateAction(DeviceState currentState) {
  switch (currentState) {
    case RedLedOn:
      // Set the red LED voltage to the maximum output voltage
      this->deviceStatus.redLedVoltage = this->deviceSettings.maxOutputVoltage;
      // Set the infrared LED voltage to the minimum output voltage
      this->deviceStatus.infraRedLedVoltage =
          this->deviceSettings.minOutputVoltage;
      // Set the red and infrared LED voltages using the PPG signal controller
      this->helperClassInstance.ppgSignalControllerPtr->setRedLED(
          this->deviceStatus.redLedVoltage);
      this->helperClassInstance.ppgSignalControllerPtr->setInfraRedLED(
          this->deviceStatus.infraRedLedVoltage);
      break;
    case InfraRedLedOn:
      // Set the red LED voltage to the minimum output voltage
      this->deviceStatus.redLedVoltage = this->deviceSettings.minOutputVoltage;
      // Set the infrared LED voltage to the maximum output voltage
      this->deviceStatus.infraRedLedVoltage =
          this->deviceSettings.maxOutputVoltage;
      // Set the red and infrared LED voltages using the PPG signal controller
      this->helperClassInstance.ppgSignalControllerPtr->setRedLED(
          this->deviceStatus.redLedVoltage);
      this->helperClassInstance.ppgSignalControllerPtr->setInfraRedLED(
          this->deviceStatus.infraRedLedVoltage);
      break;
    case PhotoDetectorReading:
      // Code to execute when PhotoDetectorReading.
      if (this->deviceStatus.statesCompleted[RedLedOn] >
          this->deviceStatus.statesCompleted[InfraRedLedOn]) {
        // Put the raw photodiode voltage into the raw red PPG signal history
        this->deviceMemory.rawRedPPGSignalHistoryPtr->put(
            this->deviceMemory.rawPhotodiodeVoltage);
      } else if (this->deviceStatus.statesCompleted[RedLedOn] ==
                 this->deviceStatus.statesCompleted[InfraRedLedOn]) {
        // Put the raw photodiode voltage into the raw infrared PPG signal
        // history
        this->deviceMemory.rawInfraRedPPGSignalHistoryPtr->put(
            this->deviceMemory.rawPhotodiodeVoltage);
      } else {
        // assert an error.
      }
      break;
    case UiIsUpdating:
      // Code to execute when UiIsUpdating.
      // Update the SpO2 value on the display
      this->helperClassInstance.displayPtr->updateSpO2(
          this->deviceMemory.spO2Value);
      // Update the heart beat rate value on the display
      this->helperClassInstance.displayPtr->updateHBR(
          this->deviceMemory.heartBeatRateValue);
      // Update the PPG wave on the display
      this->helperClassInstance.displayPtr->updatePPGWave(
          this->deviceMemory.filteredRedPPGSignalHistoryPtr);
      Serial.println("UI is updating");
      break;
    case SignalIsProcessing:
      // Code to execute when SignalIsProcessing.
      // Process the raw red PPG signal history using the filter
      this->helperClassInstance.filterPtr->process(
          this->deviceMemory.rawRedPPGSignalHistoryPtr,
          this->deviceMemory.filteredRedPPGSignalHistoryPtr);
      // Process the raw infrared PPG signal history using the filter
      this->helperClassInstance.filterPtr->process(
          this->deviceMemory.rawInfraRedPPGSignalHistoryPtr,
          this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr);
      // Calculate the SpO2 value using the filtered PPG signal histories
      this->deviceMemory.spO2Value =
          this->helperClassInstance.spO2CalculatorPtr->calculate(
              this->deviceMemory.filteredRedPPGSignalHistoryPtr,
              this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr,
              this->deviceSettings.samplingPeriodUs);
      // Calculate the heart beat rate value using the filtered PPG signal
      // histories
      this->deviceMemory.heartBeatRateValue =
          this->helperClassInstance.heartRateCalculatorPtr->calculate(
              this->deviceMemory.filteredRedPPGSignalHistoryPtr,
              this->deviceMemory.filteredInfraRedPPGSignalHistoryPtr,
              this->deviceSettings.samplingPeriodUs);
      break;
    case DeviceIdling:
      // Code to execute when DeviceIdling.
      // No specific code to execute in this state.
      while ((this->helperClassInstance.ppgSignalControllerPtr
                  ->getCurrentTimeUs() -
              this->deviceMemory.eventSequenceStartTimeUs) <=
             this->deviceSettings.samplingPeriodUs) {
        continue;
      }
      break;
    case EventSequenceStarting:
      // Code to execute when EventSequenceStarting.

      if (this->deviceStatus.statesCompleted[RedLedOn] !=
          this->deviceStatus.statesCompleted[InfraRedLedOn])
        break;

      // Reset the statesCompleted array to 0
      for (int i = 0; i < DeviceStateTotal; ++i) {
        this->deviceStatus.statesCompleted[i] = 0;
      }
      break;
    case EventSequenceEnding:
      // Code to execute when EventSequenceEnding.
      // No specific code to execute in this state.
      break;
    default:
      // Code to execute when 'state' is not any of the above cases.
      // No specific code to execute for the default case.
      break;
  }
};

/**
 * @brief Calculates the next state of the program based on the current state.
 *
 * This method determines the next state of the program based on the current
 * state.
 *
 * @param currentState The current state of the program.
 * @return The next state of the program.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
DeviceState EventController<
    voltage_data_type, time_data_type,
    pin_id_data_type>::calculateNextState(DeviceState currentState) {
  // Calculating and deciding what the next state is.
  DeviceState nextState;

  switch (currentState) {
    case RedLedOn:
      // Transition to the next state after RedLedOn.
      nextState = PhotoDetectorReading;
      break;
    case InfraRedLedOn:
      // Transition to the next state after InfraRedLedOn.
      nextState = PhotoDetectorReading;
      break;
    case PhotoDetectorReading:

      // Transition to the next state after PhotoDetectorReading.
      if ((this->helperClassInstance.ppgSignalControllerPtr
               ->getCurrentTimeUs() -
           this->deviceMemory.lastFilteredSignalUpdateTime) >=
          this->deviceSettings.screenRefreshTimeIntervalUs) {
        nextState = SignalIsProcessing;
      } else if ((this->helperClassInstance.ppgSignalControllerPtr
                      ->getCurrentTimeUs() -
                  this->deviceMemory.lastDisplayUpdateTime) >=
                 this->deviceSettings.screenRefreshTimeIntervalUs) {
        nextState = UiIsUpdating;
      } else {
        nextState = DeviceIdling;
      }
      break;

    case UiIsUpdating:
      // Transition to the next state after UiIsUpdating.
      nextState = DeviceIdling;
      break;
    case SignalIsProcessing:
      // Transition to the next state after SignalIsProcessing.
      nextState = DeviceIdling;
      break;
    case DeviceIdling:
      // Transition to the next state after DeviceIdling.
      nextState = EventSequenceEnding;
      break;
    case EventSequenceStarting:
      // Transition to the next state after EventSequenceStarting.
      // Code to execute when PhotoDetectorReading.
      if (this->deviceStatus.statesCompleted[RedLedOn] >
          this->deviceStatus.statesCompleted[InfraRedLedOn]) {
        nextState = InfraRedLedOn;
      } else if (this->deviceStatus.statesCompleted[RedLedOn] ==
                 this->deviceStatus.statesCompleted[InfraRedLedOn]) {
        nextState = RedLedOn;
      } else {
        // assert an error.
      }
      break;
    case EventSequenceEnding:
      // Transition to the next state after EventSequenceEnding.
      nextState = EventSequenceStarting;  // Loop back to the beginning.
      break;
    default:
      // Default case, return the current state.
      nextState = currentState;
      break;
  }
  return nextState;
};

/**
 * @brief Updates the count of events for the current state.
 *
 * This method increments the count of events for the current state.
 *
 * @param currentState The current state of the program.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void EventController<voltage_data_type, time_data_type, pin_id_data_type>::
    updateStateEventCount(DeviceState currentState) {
  ++(this->deviceStatus.statesCompleted[currentState]);
};
