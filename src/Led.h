#ifndef LED_h
#define LED_h

#include "Arduino.h"

class Led
{
  public:
    Led(int pin);
    void update();
    void blink(int count);
  private:
    const uint32_t _blinksOffset = 200;
    bool _currentState = false;
    uint32_t _lastBlink;
    uint32_t _pin;
    uint32_t _blinks;
};

#endif