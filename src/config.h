#ifndef CONFIG_h
#define CONFIG_h

#include "Arduino.h"

const int PIN_W0_A1 = 2;
const int PIN_W0_A2 = 3;
const int PIN_W0_B1 = 4;
const int PIN_W0_B2 = 5;

const int PIN_W1_A1 = 6;
const int PIN_W1_A2 = 7;
const int PIN_W1_B1 = 8;
const int PIN_W1_B2 = 9;

const int PIN_TURBO_BUTTON_W0 = 10;
const int PIN_TURBO_BUTTON_W1 = 11;
const int PIN_MODE_SWITCH_W0 = 12;
const int PIN_MODE_SWITCH_W1 = 13;
const int PIN_SWITCH_LED = 14;
const int PIN_POWER_SWITCH = 15;

const int TURBO_BUTTON_ROTATIONS = 200; // add 200 rotations everytime turbobutton is pressed
const int ROTATIONS_PER_INTERVAL = 3;   // add 3 rotations every interval
const int TIME_INTERVAL = 5*60;         // interval to add rotations in seconds, default value : 5*60 = 5 minutes

#endif