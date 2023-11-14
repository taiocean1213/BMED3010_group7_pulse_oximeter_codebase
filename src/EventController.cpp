#include "EventController.h"

template <class signal_data_type>
void EventController<signal_data_type>::setup() {
  // TODO set up HardwareAbstractioLevel  using the arguments baud rate,
  // analogResolutionValue, minOutputVoltage, and maxOutputVoltage ,
  // HardwareAbstractioLevel

  // TODO then pass the HardwareAbstractioLevel to the
  // PPGSignalHardwareController constructor

  // TODO set up the Display class for ui intlization

  // TODO intitlize the SignalHistory classes
}

/// @tparam signal_data_type .
template <class signal_data_type>
void EventController<signal_data_type>::loopOnce() {
  // TODO Implementation of the loopOnce function
  // This function should be easily controlled and modified by the domain
  // experts, so using abstraction that hides the sampling process in this
  // function may not be appropriate

  // TODO First check which LED is on from the class

  // TODO Then branch to change the other LED to be turned on

  // TODO Then sample the photodiode voltage after some waiting time for the LED
  // to warm up  (200 mocroseconds)

  // TODO Store the signal to the corresponding SignalHistory class

  // TODO Check if the time since the last timestamp was set from 1/60 seconds
  // ago

  // TODO If the above is `false`, then return this function

  // TODO Apply the filter to the signal

  // TODO Update the filteredSignal Class and update to the class method of
  // `Display`

  // TODO Perform hearBeatRate and SP02 computation if there is a new heart beat
  // detected

  // TODO Update the Display class by passing the HBR, SPO2

  // filtered SignalPoint
}

// Explicit instantiation
template class EventController<int>;
