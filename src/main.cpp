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

Throttle powerSwitch(PIN_POWER_SWITCH, INPUT_PULLUP);

Throttle *buttons[] = {&turboButtonW0, &turboButtonW1, &modeSwitchW0, &modeSwitchW1, &powerSwitch};

Winder winder0(PIN_W0_A1, PIN_W0_A2, PIN_W0_B1, PIN_W0_B2);
Winder winder1(PIN_W1_A1, PIN_W1_A2, PIN_W1_B1, PIN_W1_B2);

uint32_t last_run = now();
uint32_t last_run_report = 0;

#ifdef PERFORMANCE_OUTPUT
uint32_t startTime  = millis();
uint32_t runCounter = 0;
const uint32_t outputSteps = 25000;
#endif

void updateEverything();

// put your setup code here, to run once:
void setup() {
  Serial.begin(111520);
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

  if(powerSwitch.read() == true){ // Power-Button on
    led.constant(false);

    // timer reached to add new rotations
    uint16_t time_offset = now() - last_run;
    if(time_offset > TIME_INTERVAL){ 
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

      led.blink(3);    

    }else{

      if(time_offset % 10 == 0 && last_run_report != time_offset){
        char buffer[102];
        sprintf(buffer, "Time Offset = %ds, Waiting for TIME_INTERVAL = %ds to add ROTATIONS_PER_INTERVAL = %d new rotations.", time_offset, TIME_INTERVAL, ROTATIONS_PER_INTERVAL);
        Serial.println(buffer);
        last_run_report = time_offset;
      }

    }

  }else{
    led.constant(true);
  }


  #ifdef PERFORMANCE_OUTPUT
  runCounter++;
  if(runCounter == outputSteps){
    uint32_t elapsedTime = millis() - startTime; 
    double avg = (double)elapsedTime / (double)outputSteps;

    char buffer[100];
    sprintf(buffer, "Performance Output: %ld loop runs, elapsed %ld ms total, average %s ms per loop", outputSteps, elapsedTime, String(avg, 5).c_str());
    Serial.println(buffer);

    startTime = millis();
    runCounter = 0;
  }
  #endif

}

void updateEverything(){
  // update LED to make it blink, when needed.
  led.update();

  // update Buttons/Switch
  for (Throttle *button: buttons) {
    button->update();
  }

  // update winders
  winder0.update();
  winder1.update();
}