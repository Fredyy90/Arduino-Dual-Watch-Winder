#include <Arduino.h>
#include <Winder.h>


Winder::Winder(uint8_t step_pin, uint8_t direction_pin){
    this->_stepper = AccelStepper(AccelStepper::DRIVER, step_pin, direction_pin);
    this->_setStepperParameters();
}

Winder::Winder(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4){
    this->_stepper = AccelStepper(AccelStepper::FULL4WIRE, pin1, pin2, pin3, pin4);
    this->_setStepperParameters();
}

void Winder::_setStepperParameters(){
    this->_stepper.setMaxSpeed(this->_maxSpeed); 
    this->_stepper.setAcceleration(this->_acceleration);
}

void Winder::update(){
    this->_stepper.run();

    if(this->isRunning()){
        this->_lastStepTime = millis();
        return;
    }

    // stepper is not running
    if(this->_CWRotations == 0 && this->_CCWRotations == 0){
        if(this->_lastStepTime + this->_stepperTimeout >= millis()){
            this->_stepper.disableOutputs();
            this->_stepper.setCurrentPosition(0);
        }
    }else if(this->_CWRotations > 0){
        this->_stepper.move(this->_stepsPerRotation * this->_CWRotations);  
        this->_CWRotations = 0;
    }else if(this->_CCWRotations > 0){
        this->_stepper.move(-this->_stepsPerRotation * this->_CCWRotations);  
        this->_CCWRotations = 0;
    }
}

bool Winder::isRunning(){
    return this->_stepper.isRunning();
}

bool Winder::stop(){

    if(!this->isRunning()){
        return false;
    }

    // stepper is running
    long distance = this->_stepper.distanceToGo();
    if(distance > 0){
        this->_stepper.move(distance % this->_stepsPerRotation);
    }else{
        this->_stepper.move(-this->_stepsPerRotation + (distance  % this->_stepsPerRotation));
    }

    this->_CCWRotations = 0;
    this->_CWRotations = 0;

    return true;

}

void Winder::addRotations(const u_int8_t count){
    this->addRotations(count, Winder::SPLIT);
}

void Winder::addRotations(const u_int8_t count, const u_int8_t direction){

    if(direction == Winder::FORWARD){
        this->_CWRotations += count;
    }else if (direction == Winder::BACKWARD){
        this->_CCWRotations += count;
    }else if (direction == Winder::RANDOM){
        const int rand = random(256);
        if(rand <= 127){
            this->_CWRotations += count;
        }else{
            this->_CCWRotations += count;
        }
    }else if (direction == Winder::RANDOM_SPLIT){
        float factor = ((float)random(256) / (float)256);
        const int CWRotations = count * factor;
        this->_CWRotations += CWRotations;
        this->_CCWRotations += count - CWRotations;
    }else if (direction == Winder::SPLIT){
        const int CWRotations = count / 2;
        this->_CWRotations += CWRotations;
        this->_CCWRotations += count - CWRotations;
    }

}