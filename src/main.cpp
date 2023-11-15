#include <Arduino.h>
#undef min //for muting the `Arduino.h` in-built min() function
#undef max //for muting the `Arduino.h` in-built max() function

#include "Display.h"
#include "HardwareAbstractionLayer.h"
#include "HeartRateCalculator.h"
#include "PPGSignalHardwareController.h"
#include "SignalHistory.h"
#include "SpO2Calculator.h"

void setup() {}

void loop() {
  // put your main code here, to run repeatedly:
}
