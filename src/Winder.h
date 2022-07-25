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
    const uint32_t _stepsPerRotation = 2048;
    const uint32_t _stepsDelay = 2;
    uint32_t _CWSteps = 0;
    uint32_t _CCWSteps = 0;
    uint32_t _lastStep = 0;
};

#endif