/**
 * @interface EventController
 * @brief Abstract base class for displaying values.
 */

#ifndef EVENTCONTROLLERINTERFACE_H
#define EVENTCONTROLLERINTERFACE_H
class EventControllerInterface {
 public:
  virtual ~EventControllerInterface() {}
  virtual void loopOnce() = 0;
};
#endif