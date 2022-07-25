#include "Arduino.h"
#include <Led.h>

Led::Led(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(this->_pin, LOW);
  this->_pin = pin;
  this->_lastBlink = millis();
}

void Led::update()
{

    uint32_t currentTime = millis();
 	if ((currentTime - this->_lastBlink) >= this->_blinksOffset) {
 		this->_lastBlink = currentTime;
        
        if(this->_blinks > 0 && this->_currentState == false){
            digitalWrite(this->_pin, HIGH);
            this->_blinks -= 1;
        }else{
            digitalWrite(this->_pin, LOW);
        }
        
    }
}

void Led::blink(int count)
{
  this->_blinks += count;  
}