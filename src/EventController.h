#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <map>

#include "biomedical_metrics/HeartRateCalculatorInterface.h"
#include "biomedical_metrics/SpO2CalculatorInterface.h"
#include "event_controller/EventControllerInterface.h"
#include "hardware_driver_apis/HardwareAbstractionLayerInterface.h"
#include "ppg_signal_io/PPGSignalHardwareControllerInterface.h"
#include "signal_filter/FastFourierTransformInterface.h"
#include "signal_filter/FilterInterface.h"
#include "signal_history/SignalHistoryInterface.h"
#include "user_interface/Displayinterface.h"
/**
 * @brief EventController class template for handling events.
 *
 * This class is a template class that takes a signal_data_type as a parameter.
 * It has two methods: setup and loopOnce.
 * The setup method initializes the HardwareAbstractionLayer,
 * PPGSignalHardwareController, Display, and SignalHistory classes. The loopOnce
 * method implements the logic for the main loop of the event controller.
 */
template <class voltage_data_type, class time_data_type, class pin_id_data_type>
class EventController : public EventControllerInterface {
 public:
  /**
   * @brief LoopOnce method for implementing the logic for the main loop of the
   * event controller.
   */
  void loopOnce() override;

  // Constructors
  EventController();

  // Destructor
  ~EventController();

 private:
  typedef struct HelperClassInstanceStruct {
    HardwareAbstractionLayerInterface<voltage_data_type, time_data_type,
                                      pin_id_data_type>* hardwareLayerPtr;
    PPGSignalHardwareControllerInterface<voltage_data_type, time_data_type,
                                         pin_id_data_type>*
        ppgSignalControllerPtr;
    DisplayInterface<voltage_data_type>* displayPtr;
    FastFourierTransformInterface<voltage_data_type>* fftPtr;
    FilterInterface<voltage_data_type, voltage_data_type>* filterPtr;
    SpO2CalculatorInterface<voltage_data_type>* spO2CalculatorPtr;
    HeartRateCalculatorInterface<voltage_data_type>* heartRateCalculatorPtr;
  } helper_class_instance_data_type;

  typedef enum {
    RedLedOn,
    InfraRedLedOn,
    PhotoDetectorReading,
    UiIsUpdating,
    SignalIsProcessing,
    DeviceIdling,
    EventSequenceStarting,
    EventSequenceEnding,
    DeviceStateTotal
  } DeviceState;

  // Struct members that can be configured for the device.
  typedef struct DeviceSettings {
    int analogResolutionValue;
    int baudRate;
    voltage_data_type minOutputVoltage;
    voltage_data_type maxOutputVoltage;
    std::vector<std::pair<voltage_data_type, voltage_data_type>> passbandsHz;
    std::vector<std::pair<voltage_data_type, voltage_data_type>> stopbandsHz;
    voltage_data_type samplingFrequencyHz;
    voltage_data_type signalHistoryElementsCount;
    voltage_data_type photoDiodeWarmupTimeUs;
  } device_settings_data_type;

  // Struct members that can be actively controlled by the device.
  typedef struct DeviceStatus {
    voltage_data_type redLedVoltage;
    voltage_data_type infraRedLedVoltage;
    DeviceState deviceState;
    int statesCompleted[DeviceStateTotal];
  } device_status_data_type;

  // Struct members that is measured and recorded by the device.
  typedef struct DeviceMemory {
    voltage_data_type rawPhotodiodeVoltage;
    time_data_type eventSequenceStartTimeUs;
    time_data_type eventSequenceEndTimeUs;
    SignalHistoryInterface<voltage_data_type>* rawRedPPGSignalHistoryPtr;
    SignalHistoryInterface<voltage_data_type>* filteredRedPPGSignalHistoryPtr;
    SignalHistoryInterface<voltage_data_type>* rawInfraRedPPGSignalHistoryPtr;
    SignalHistoryInterface<voltage_data_type>*
        filteredInfraRedPPGSignalHistoryPtr;
  } device_memory_data_type;

  helper_class_instance_data_type helperClassInstance;
  device_settings_data_type deviceSettings;
  device_memory_data_type deviceMemory;
  device_status_data_type deviceStatus;
};

// TODO explicit instantiation required
template class EventController<double, int, int>;

// using keyword definition
// using EventControllerDefaultClass = EventController<double, int, int>;

#endif
