#if !defined(WINDER_h)
#define WINDER_h

#include <Arduino.h>
#include <Config.h>
#include <AccelStepper.h>

class Winder
{
  public:
    Winder(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    Winder(uint8_t step_pin, uint8_t direction_pin);
    void update();
    bool isRunning();
    bool stop();
    void addRotations(uint8_t count);
    void addRotations(uint8_t count, uint8_t direction);

    static const uint8_t FORWARD = 1;
    static const uint8_t BACKWARD = 2;
    static const uint8_t RANDOM = 3;
    static const uint8_t RANDOM_SPLIT = 4;
    static const uint8_t SPLIT = 5;

  private:
    void _setStepperParameters();
    AccelStepper _stepper;
    const uint32_t _stepsPerRotation = STEPPER_STEPS_PER_ROTATION;
    const uint32_t _maxSpeed = STEPPER_MAX_STEPS_PER_SEC;
    const uint32_t _acceleration = STEPPER_ACCELERATION;
    const uint32_t _stepperTimeout = 1000; // 1 second
    uint32_t _lastStepTime = 0;
    uint32_t _CWRotations = 0;
    uint32_t _CCWRotations = 0;
    uint32_t _lastStep = 0;
};

#endif