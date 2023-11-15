#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <Arduino.h>
#undef min  // for muting the `Arduino.h` in-built min() function
#undef max  // for muting the `Arduino.h` in-built max() function

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