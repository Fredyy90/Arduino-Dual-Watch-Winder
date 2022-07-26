#ifndef WINDER_h
#define WINDER_h

#include <Arduino.h>
#include <AccelStepper.h>

class Winder
{
  public:
    Winder(int pin1, int pin2, int pin3, int pin4);
    void update();
    void addRotations(int count);
    void addRotations(int count, int direction);

    const int FORWARD = 1;
    const int BACKWARD = 1;
    const int RANDOM = 1;
    const int RANDOM_SPLIT = 1;

  private:
    AccelStepper _stepper;
    const uint32_t _stepsPerRotation = 2048;        // steps needed for 1 rotation
    const uint32_t _maxSpeed = _stepsPerRotation/4; // max speed in steps per second
    const uint32_t _acceleration = 128;             // in steps*second²
    uint32_t _CWSteps = 0;
    uint32_t _CCWSteps = 0;
    uint32_t _lastStep = 0;
};

#endif