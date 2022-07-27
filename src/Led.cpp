#include <Arduino.h>
#include <Led.h>

Led::Led(int pin){
  pinMode(pin, OUTPUT);
  digitalWrite(this->_pin, LOW);
  this->_pin = pin;
  this->_lastBlink = millis();
}

void Led::update(){

    if(this->_mode == Led::CONSTANT){
        return;
    }

    uint32_t currentTime = millis();
 	if ((currentTime - this->_lastBlink) >= this->_blinksOffset) {
 		this->_lastBlink = currentTime;

        if(this->_blinks > 0 && this->_currentState == true){
            this->_blinks -= 1;
        }else if(this->_blinks == 0){
                this->_mode = Led::CONSTANT;
        }
        this->_toggle();
    }
}

void Led::_toggle(){
    this->_toggle(!this->_currentState);
}

void Led::_toggle(bool state){
    this->_currentState = state;
    digitalWrite(this->_pin, this->_currentState);
}

void Led::constant(bool state){
    if(this->_blinks <= 0){
        this->_mode = Led::CONSTANT;
        this->_toggle(state);
    }
}

void Led::addBlinks(int count){
    this->_mode = Led::BLINK;
    this->_blinks += count;
}