#ifndef WINDER_h
#define WINDER_h

#include <Arduino.h>
#include <AccelStepper.h>

class Winder
{
  public:
    Winder(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    Winder(uint8_t step_pin, uint8_t direction_pin);
    void update();
    void addRotations(int count);
    void addRotations(int count, int direction);

    const int FORWARD = 1;
    const int BACKWARD = 2;
    const int RANDOM = 3;
    const int RANDOM_SPLIT = 4;

  private:
    void _setStepperParameters();
    AccelStepper _stepper;
    const uint32_t _stepsPerRotation = 2048;        // steps needed for 1 rotation
    const uint32_t _maxSpeed = 600;                 // max speed in steps per second
    const uint32_t _acceleration = 2048;            // in steps*second²
    uint32_t _CWRotations = 0;
    uint32_t _CCWRotations = 0;
    uint32_t _lastStep = 0;
};

#endif