
/**
 * @interface SignalHistoryInterface
 * @brief Template class for storing history
 * of discrete signal intensity.
 *
 */

#ifndef SIGNAL_HISTORY_SIGNALHISTORYINTERFACE_H
#define SIGNAL_HISTORY_SIGNALHISTORYINTERFACE_H
template <class element_type>
class SignalHistoryInterface {
 public:
  virtual void put(element_type signal) = 0;
  virtual element_type get(element_type nthSample) = 0;
  virtual void reset() = 0;

 private:
  virtual element_type getEntryPointIndex() = 0;
  virtual void updateEntryPointIndex() = 0;
};

#endif
