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
 * This constructor initializes the HardwareAbstractionLayer,
 * PPGSignalHardwareController, Display, and SignalHistory classes.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
EventController<voltage_data_type, time_data_type,
                pin_id_data_type>::EventController() {
  this->setup();
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
  // Delete the objects

  delete hardwareLayerInstancePtr;
  delete ppgSignalControllerInstancePtr;
  delete displayInstancePtr;
  delete signalHistoryInstancePtr;
  delete fftInstancePtr;
  delete filterInstancePtr;
  delete spO2CalculatorInstancePtr;
  delete heartRateCalculatorInstancePtr;
};
/**
 * @brief Setup method for initializing the HardwareAbstractionLayer,
 * PPGSignalHardwareController, Display, and SignalHistory classes.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void EventController<voltage_data_type, time_data_type,
                     pin_id_data_type>::setup() {
  // Initialize the objects using new keyword
  hardwareLayerInstancePtr =
      new HardwareAbstractionLayer<voltage_data_type, time_data_type,
                                   pin_id_data_type>(12, 38400, 0, 3.3);

  ppgSignalControllerInstancePtr =
      new PPGSignalHardwareController<voltage_data_type, time_data_type,
                                      pin_id_data_type>(
          hardwareLayerInstancePtr);

  displayInstancePtr = new Display<voltage_data_type>();
  displayInstancePtr->begin();

  signalHistoryInstancePtr = new SignalHistory<voltage_data_type>(50);
  signalHistoryInstancePtr->reset();

  fftInstancePtr = new FastFourierTransform<voltage_data_type>();

  std::vector<std::pair<voltage_data_type, voltage_data_type>> passbands = {
      {1, 2}, {3, 4}};
  std::vector<std::pair<voltage_data_type, voltage_data_type>> stopbands = {
      {5, 6}, {7, 8}};
  voltage_data_type samplingFrequency = 40;

  filterInstancePtr = new Filter<voltage_data_type, voltage_data_type>(
      passbands, stopbands, samplingFrequency, fftInstancePtr);

  spO2CalculatorInstancePtr = new SpO2Calculator<voltage_data_type>();
  heartRateCalculatorInstancePtr = new HeartRateCalculator<voltage_data_type>();

  /*
// Set up HardwareAbstractionLayer using the arguments baud rate,
// analogResolutionValue, minOutputVoltage, and maxOutputVoltage
*hardwareLayer =
new HardwareAbstractionLayerInterface<voltage_data_type, time_data_type,
                        pin_id_data_type>(
baud_rate, analogResolutionValue, minOutputVoltage, maxOutputVoltage);

// Pass the HardwareAbstractionLayer to the PPGSignalHardwareController
// constructor
*ppgSignalController = new PPGSignalHardwareControllerInterface<
voltage_data_type, time_data_type, pin_id_data_type>(*hardwareLayer);

// Initialize the Display class for UI initialization
*display = new DisplayInterface<values_data_type>();
(*display)->begin();

// Initialize the SignalHistory classes
*signalHistory = new SignalHistoryInterface<element_type>();
(*signalHistory)->reset();
*/
};
/**
 * @brief LoopOnce method for implementing the logic for the main loop of the
 * event controller.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
void EventController<voltage_data_type, time_data_type,
                     pin_id_data_type>::loopOnce(){
    /*
  // Check which LED is on from the class
  bool isRedLedOn = (*ppgSignalController)->getRedLED();
  bool isInfraRedLedOn = (*ppgSignalController)->getInfraRedLED();

  // Change the other LED to be turned on
  if (isRedLedOn) {
  (*ppgSignalController)->setInfraRedLED(voltage_data_type);
  } else if (isInfraRedLedOn) {
  (*ppgSignalController)->setRedLED(voltage_data_type);
  };
  // Sample the photodiode voltage after some waiting time for the LED to warm
  // up (200 microseconds)
  voltage_data_type photodiodeVoltage =
  (*ppgSignalController)->getPhotoDiodeVoltage(200);

  // Store the signal to the corresponding SignalHistory class
  (*signalHistory)->put(photodiodeVoltage);

  // Check if the time since the last timestamp was set from 1/60 seconds ago
  if (!((*signalHistory)->getEntryPointIndex() == 1 / 60)) {
  return;
  };
  // Apply the filter to the signal
  *fft = new FastFourierTransformInterface<element_datatype>();
  *filter = new FilterInterface<element_data_type, frequency_datatype>();
  std::vector<element_data_type> filteredSignal = (*filter)->filter(
  (*fft)->fastFourierTransform((*signalHistory)->get(nthSample)));

  // Update the filteredSignal Class and update to the class method of `Display`
  (*display)->updatePPGWave(filteredSignal.data(), filteredSignal.size(),
          min_ppg_value, max_ppg_value);

  // Perform heartBeatRate and SP02 computation if there is a new heart beat
  // detected
  *spO2Calculator = new SpO2CalculatorInterface<element_type>();
  *heartRateCalculator = new HeartRateCalculatorInterface<element_type>();
  element_type spo2Value = (*spO2Calculator)->calculate(filteredSignal);
  element_type hrValue = (*heartRateCalculator)->calculate(filteredSignal);

  // Update the Display class by passing the HBR, SPO2 filtered SignalPoint
  (*display)->updateSpO2(spo2Value);
  (*display)->updateHBR(hrValue);
  */
};
