#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <Arduino.h>

#include "event_controller/EventControllerInterface.h"

template <class signal_data_type>
class EventController : public EventControllerInterface<signal_data_type> {
 public:
  /**
   * @brief Sets up the event controller.
   */
  void setup() override;

  /**
   * @brief Runs the event controller once.
   */
  void loopOnce() override;
};

#endif