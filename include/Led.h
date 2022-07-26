#ifndef LED_h
#define LED_h

#include <Arduino.h>

class Led
{
  public:
    Led(int pin);
    void update();
    void blink(int count);
    void constant(bool state);

    const int BLINK = 1;
    const int CONSTANT = 2;

  private:
    const uint32_t _blinksOffset = 400;
    bool _currentState = false;
    uint8_t _mode = BLINK;
    uint32_t _lastBlink;
    uint32_t _pin;
    uint32_t _blinks;
};

#endif