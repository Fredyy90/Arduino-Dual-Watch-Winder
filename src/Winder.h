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
    const int BACKWARD = 2;
    const int RANDOM = 3;
    const int RANDOM_SPLIT = 4;

  private:
    AccelStepper _stepper;
    const uint32_t _stepsPerRotation = 2048;        // steps needed for 1 rotation
    const uint32_t _maxSpeed = _stepsPerRotation/3; // max speed in steps per second
    const uint32_t _acceleration = 512;             // in steps*second²
    uint32_t _CWRotations = 0;
    uint32_t _CCWRotations = 0;
    uint32_t _lastStep = 0;
};

#endif