/**
 * @interface EventController
 * @brief Abstract base class for displaying values.
 */

#ifndef EVENTCONTROLLERINTERFACE_H
#define EVENTCONTROLLERINTERFACE_H
template <class signal_data_type>
class EventControllerInterface {
public:
   virtual void setup() = 0;
   virtual void run() = 0;

};
#endif