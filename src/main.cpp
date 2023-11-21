#include <Arduino.h>

#undef Min
#undef Max
#undef abs
#undef min  // for muting the `Arduino.h` in-built min() function
#undef max  // for muting the `Arduino.h` in-built max() function

#include "EventController.h"

// Declare class in heap.
EventController<double, int, int>* eventControllerClassObject;

void setup() {
  // Initialize the EventController Class in the heap
  eventControllerClassObject = new EventController<double, int, int>();
  eventControllerClassObject->setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  eventControllerClassObject->loopOnce();
}
