#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include "EventController.h"
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
   * @brief Setup method for initializing the HardwareAbstractionLayer,
   * PPGSignalHardwareController, Display, and SignalHistory classes.
   */
  void setup() override;

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
  HardwareAbstractionLayerInterface<voltage_data_type, time_data_type,
                                    pin_id_data_type>* hardwareLayerInstancePtr;
  PPGSignalHardwareControllerInterface<voltage_data_type, time_data_type,
                                       pin_id_data_type>*
      ppgSignalControllerInstancePtr;
  DisplayInterface<voltage_data_type>* displayInstancePtr;
  SignalHistoryInterface<voltage_data_type>* signalHistoryInstancePtr;
  FastFourierTransformInterface<voltage_data_type>* fftInstancePtr;
  FilterInterface<voltage_data_type, voltage_data_type>* filterInstancePtr;
  SpO2CalculatorInterface<voltage_data_type>* spO2CalculatorInstancePtr;
  HeartRateCalculatorInterface<voltage_data_type>*
      heartRateCalculatorInstancePtr;
};

// TODO explicit instantiation required
template class EventController<double, int, int>;

// using keyword definition
// using EventControllerDefaultClass = EventController<double, int, int>;

#endif
