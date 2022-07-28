#if !defined(WINDER_h)
#define WINDER_h

#include <Arduino.h>
#include <Config.h>
#include <AccelStepper.h>

class Winder
{
  public:
    Winder(u_int8_t pin1, u_int8_t pin2, u_int8_t pin3, u_int8_t pin4);
    Winder(u_int8_t step_pin, u_int8_t direction_pin);
    void update();
    bool isRunning();
    bool stop();
    void addRotations(u_int8_t count);
    void addRotations(u_int8_t count, u_int8_t direction);

    static const u_int8_t FORWARD = 1;
    static const u_int8_t BACKWARD = 2;
    static const u_int8_t RANDOM = 3;
    static const u_int8_t RANDOM_SPLIT = 4;

  private:
    void _setStepperParameters();
    AccelStepper _stepper;
    const u_int32_t _stepsPerRotation = STEPPER_STEPS_PER_ROTATION;
    const u_int32_t _maxSpeed = STEPPER_MAX_STEPS_PER_SEC;
    const u_int32_t _acceleration = STEPPER_ACCELERATION;
    const u_int32_t _stepperTimeout = 1000; // 1 second
    u_int32_t _lastStepTime = 0;
    u_int32_t _CWRotations = 0;
    u_int32_t _CCWRotations = 0;
    u_int32_t _lastStep = 0;
};

#endif