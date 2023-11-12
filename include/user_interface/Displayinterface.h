
/**
 * @interface Display
 * @brief Abstract base class for displaying values.
 */

#ifndef USER_INTERFACE_DISPLAYINTERFACE_H
#define USER_INTERFACE_DISPLAYINTERFACE_H
template <class values_data_type>
class DisplayInterface {
 public:
  virtual void setupUI() = 0;

  virtual void displayHeartRate(values_data_type heartRate) = 0;
  virtual void displaySpO2(values_data_type spo2Value) = 0;
  virtual void displayPPGDataPoint(values_data_type ppgDataPoint) = 0;
};

#endif
