#include <Arduino.h>
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
    if(this->_mode != Led::BLINK){
        return;
    }

    uint32_t currentTime = millis();
 	if ((currentTime - this->_lastBlink) >= this->_blinksOffset) {
 		this->_lastBlink = currentTime;

        if(this->_blinks > 0 && this->_currentState == false){
            digitalWrite(this->_pin, HIGH);
            this->_currentState = true;
            this->_blinks -= 1;
        }else{
            digitalWrite(this->_pin, LOW);
            this->_currentState = false;
            if(this->_blinks == 0){
                this->_mode = Led::CONSTANT;
            }
        }

    }
}

void Led::constant(bool state){
    if(this->_blinks <= 0){
        this->_mode = Led::CONSTANT;
        this->_currentState = state;
        digitalWrite(this->_pin, state);
    }
}

void Led::blink(int count)
{
    this->_mode = Led::BLINK;
    this->_blinks += count;
}