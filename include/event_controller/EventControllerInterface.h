/**
 * @interface EventControllerInterface
 * @brief Abstract base class for displaying values.
 *
 * This interface defines the contract for classes that need to implement a
 * loopOnce method.
 */
#ifndef EVENTCONTROLLERINTERFACE_H
#define EVENTCONTROLLERINTERFACE_H
class EventControllerInterface {
 public:
  /**
   * @brief Virtual destructor.
   *
   * This is a virtual destructor to ensure that the destructor of the derived
   * class is called.
   */
  virtual ~EventControllerInterface() {}

  /**
   * @brief Pure virtual function to be implemented by derived classes.
   *
   * This function needs to be implemented by any class that inherits from this
   * interface.
   */
  virtual void loopOnce() = 0;
};
#endif
