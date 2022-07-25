#include <Arduino.h>
#include <Winder.h>

Winder::Winder(int pin1, int pin2, int pin3, int pin4){
    this->_stepper = AccelStepper(AccelStepper::FULL4WIRE, pin1, pin2, pin3, pin4);
    this->_stepper.setMaxSpeed(1.0);
    this->_stepper.setAcceleration(0.0);
}

void Winder::update(){
    this->_stepper.run();

    if(this->_CWSteps == 0 && this->_CCWSteps == 0 && !this->_stepper.isRunning()){
        this->_stepper.disableOutputs();
    }
}

void Winder::addRotations(const int count){
    this->addRotations(count, Winder::RANDOM_SPLIT);
}

void Winder::addRotations(const int count, const int direction){

    if(direction == Winder::FORWARD){
        this->_CWSteps += this->_stepsPerRotation * count;
    }else if (direction == Winder::BACKWARD){
        this->_CCWSteps += this->_stepsPerRotation * count;
    }else if (direction == Winder::RANDOM){
        const int rand = random(256);
        if(rand <= 127){
            this->_CWSteps += this->_stepsPerRotation * count;
        }else{            
            this->_CCWSteps += this->_stepsPerRotation * count;
        }
    }else if (direction == Winder::RANDOM_SPLIT){
        float factor = (random(256)/256);
        const int CWSteps = count * factor;
        this->_CWSteps += this->_stepsPerRotation * CWSteps;   
        this->_CCWSteps += this->_stepsPerRotation * (count - CWSteps);
    }
    

}