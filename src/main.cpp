#include <config.h>
#include <Arduino.h>
#include <Throttle.h>
#include <Led.h>
#include <TimeLib.h>

Led led(PIN_SWITCH_LED);

Throttle turboButtonW0(PIN_TURBO_BUTTON_W0, INPUT_PULLUP);
Throttle turboButtonW1(PIN_TURBO_BUTTON_W1, INPUT_PULLUP);

Throttle modeSwitchW0(PIN_MODE_SWITCH_W0, INPUT_PULLUP);
Throttle modeSwitchW1(PIN_MODE_SWITCH_W1, INPUT_PULLUP);

uint32_t last_run = now();

// put your setup code here, to run once:
void setup() {
  Serial.begin(111520);
}


// put your main code here, to run repeatedly:
void loop() {

  // update LED to make it blink, when needed.
  led.update();

  // update Buttons/Switch
  turboButtonW0.update(); 
  turboButtonW1.update();
  modeSwitchW0.update();
  modeSwitchW1.update();

  // update winders
  /*
    TODO: update winders
  */

  // add rotations if turbo-button pressed
  if (turboButtonW0.rose()) {
    led.blink(3);
      /*
        TODO: add `TURBO_BUTTON_ROTATIONS` rotations to Winder0
      */
  }

  if (turboButtonW1.rose()) {
    led.blink(3);
      /*
        TODO: add `TURBO_BUTTON_ROTATIONS` rotations to Winder1
      */
  }

  // timer reached to add new rotations
  if((now() - last_run) > TIME_INTERVAL){ 

    last_run = now();

    bool modeW0State = modeSwitchW0.read();
    bool modeW1State = modeSwitchW1.read();
    if(modeW0State == false && modeW1State == false){
      /*
        TODO: add `ROTATIONS_PER_INTERVAL` rotations to both winders
      */
    }else if (modeW0State == true){
      /*
        TODO: add `ROTATIONS_PER_INTERVAL` rotations to Winder0
      */
    }else if (modeW0State == true){
      /*
        TODO: add `ROTATIONS_PER_INTERVAL` rotations to Winder1
      */
    }
    

  }

}