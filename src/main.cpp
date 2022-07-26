#include <config.h>
#include <Arduino.h>
#include <Throttle.h>
#include <Led.h>
#include <TimeLib.h>
#include <Winder.h>

Led led(PIN_SWITCH_LED);

Throttle turboButtonW0(PIN_TURBO_BUTTON_W0, INPUT_PULLUP);
Throttle turboButtonW1(PIN_TURBO_BUTTON_W1, INPUT_PULLUP);

Throttle modeSwitchW0(PIN_MODE_SWITCH_W0, INPUT_PULLUP);
Throttle modeSwitchW1(PIN_MODE_SWITCH_W1, INPUT_PULLUP);

Winder winder0(PIN_W0_A1, PIN_W0_A2, PIN_W0_B1, PIN_W0_B2);
Winder winder1(PIN_W1_A1, PIN_W1_A2, PIN_W1_B1, PIN_W1_B2);

uint32_t last_run = now();

void updateEverything();

// put your setup code here, to run once:
void setup() {
  Serial.begin(111520);
  delay(10000);
}

// put your main code here, to run repeatedly:
void loop() {

  updateEverything();

  // add rotations if turbo-button pressed
  if (turboButtonW0.fell()) {
    Serial.println("TurboButtonW0 triggered");
    led.blink(3);
    winder0.addRotations(TURBO_BUTTON_ROTATIONS);
  }

  if (turboButtonW1.fell()) {
    Serial.println("TurboButtonW1 triggered");
    led.blink(3);
    winder1.addRotations(TURBO_BUTTON_ROTATIONS);
  }

  // timer reached to add new rotations
  if((now() - last_run) > TIME_INTERVAL){ 
    Serial.println("TIME_INTERVAL reached to add new rotations");

    last_run = now();

    bool modeW0State = modeSwitchW0.read();
    bool modeW1State = modeSwitchW1.read();
    if(modeW0State == true && modeW1State == true){
      Serial.println("Added rotations to both winders");
      winder0.addRotations(ROTATIONS_PER_INTERVAL);
      winder1.addRotations(ROTATIONS_PER_INTERVAL);
    }else if (modeW0State == false){
      Serial.println("Added rotations to winder0");
      winder0.addRotations(ROTATIONS_PER_INTERVAL);
    }else if (modeW1State == false){
      Serial.println("Added rotations to winder1");
      winder1.addRotations(ROTATIONS_PER_INTERVAL);
    }
    

  }

}



void updateEverything(){
  // update LED to make it blink, when needed.
  led.update();

  // update Buttons/Switch
  turboButtonW0.update(); 
  turboButtonW1.update();
  modeSwitchW0.update();
  modeSwitchW1.update();

  // update winders
  winder0.update();
  winder1.update();
}