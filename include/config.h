#if !defined(CONFIG_h)
#define CONFIG_h

#include <Arduino.h>


#define NUMBER_OF_WINDERS 2      // number of winders to control, can only be 1 or 2
#define HAS_TURBO_BUTTONS 1      // add support for turbo buttons, connected to pins PIN_TURBO_BUTTON_W0 and PIN_TURBO_BUTTON_W1
//#define HAS_SOFT_POWER_SWITCH 1  // add support for "soft" power switch, connected to pin PIN_POWER_SWITCH and not directly to the power supply
//#define HAS_LED 1                // uncomment if you connect a LED to pin PIN_POWER_SWITCH_LED e.g. the LED in the power switch
//#define HAS_MODE_SWITCHES 1      // add support for mode switches, connected to pins PIN_MODE_SWITCH_W0 and PIN_MODE_SWITCH_W1
#define PERFORMANCE_OUTPUT 1     // add additional debug output about the loop performance every 25k runs

/** 
 *  3600 / TIME_INTERVAL * 24 *  ROTATIONS_PER_INTERVAL = rotations per day
 * 
 *  TIME_INTERVAL | ROTATIONS_PER_INTERVAL | rotations per day
 *  1  * 60       |  1                     | 1140
 *  10 * 60       | 10                     | 1140
 *  2  * 60       |  1                     |  720
 *  20 * 60       | 10                     |  720
 *  5  * 60       |  3                     |  864
 *  5  * 60       |  2                     |  576
 * 
 */

const int ROTATIONS_PER_INTERVAL = 3;               // add 3 rotations every interval
const int TIME_INTERVAL          = 5*60;            // interval to add rotations in seconds, default value : 5*60 = 5 minutes
const int TURBO_BUTTON_ROTATIONS = 200;             // add 200 rotations everytime turbobutton is pressed

// define what kind of driver you want to use, you can only choose type of driver at a time
//#define DRIVER_ULN2003 1        // uncomment if you use a ULN2003 driver
#define DRIVER_TMC220x 1        // uncomment if you use a TMC220x driver

#if defined(DRIVER_ULN2003)
    // define pins used for first winder
    const int PIN_W0_A1 = 2;
    const int PIN_W0_A2 = 3;
    const int PIN_W0_B1 = 4;
    const int PIN_W0_B2 = 5;
    
    #if NUMBER_OF_WINDERS > 1
        // define pins used for second winder
        const int PIN_W1_A1 = 6; 
        const int PIN_W1_A2 = 7;
        const int PIN_W1_B1 = 8;
        const int PIN_W1_B2 = 9;
    #endif
#endif

#if defined(DRIVER_TMC220x)
    // define pins used for first winder
    const int PIN_W0_STP = 2;
    const int PIN_W0_DIR = 5;

    #if NUMBER_OF_WINDERS > 1
        // define pins used for second winder
        const int PIN_W1_STP = 3; 
        const int PIN_W1_DIR = 6;
    #endif

    // define pin if only 1 pin controls both steppers
    #define PIN_STEPPER_ENABLE 8
#endif

// define pins used for the turbo buttons if HAS_TURBO_BUTTONS is defined
#if defined(HAS_TURBO_BUTTONS)
    const int PIN_TURBO_BUTTON_W0 = 10;
    #if NUMBER_OF_WINDERS > 1
        const int PIN_TURBO_BUTTON_W1 = 11;
    #endif
#endif

// define pins used for the mode switch
#if defined(HAS_MODE_SWITCH) && NUMBER_OF_WINDERS > 1
    const int PIN_MODE_SWITCH_W0  = 12;
    const int PIN_MODE_SWITCH_W1  = 13;
#endif

#if defined(HAS_LED)
    const int PIN_POWER_SWITCH_LED = 14;
#endif

#if defined(HAS_SOFT_POWER_SWITCH)
    //define pins used for the power switch
    const int PIN_POWER_SWITCH     = 15;
#endif

#if defined(DRIVER_ULN2003)
    const uint32_t STEPPER_STEPS_PER_ROTATION = 2038;  // steps needed for 1 rotation (https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/)
    const uint32_t STEPPER_MAX_STEPS_PER_SEC  = 600;   // max speed in steps per second
    const uint32_t STEPPER_ACCELERATION       = 2048;  // in steps*second²
#endif

#if defined(DRIVER_TMC220x)
    const uint32_t STEPPER_STEPS_PER_ROTATION = 200*64;  // steps needed for 1 rotation | 360°/1,8° per step = 200 steps * microsteps = 200*60 = 12000 steps per rotation
    const uint32_t STEPPER_MAX_STEPS_PER_SEC  = STEPPER_STEPS_PER_ROTATION/4;   // max speed in steps per second
    const uint32_t STEPPER_ACCELERATION       = 2048;    // in steps*second²
#endif


#if !defined(HAS_LED) && defined(LED_BUILTIN)
    #define HAS_LED 1
    const int PIN_POWER_SWITCH_LED = LED_BUILTIN;
#endif

/**
 * throw errors if config is not valid
 */

#if defined(DRIVER_ULN2003) && defined(DRIVER_TMC220x)
    #error "You can only use one driver!"
#endif

#if !defined(NUMBER_OF_WINDERS) || NUMBER_OF_WINDERS < 1 || NUMBER_OF_WINDERS > 2
    #error "Please define NUMBER_OF_WINDERS to be a valid vaule 1 or 2!"
#endif

#endif // CONFIG_h