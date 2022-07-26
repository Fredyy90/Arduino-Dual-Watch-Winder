#include <Arduino.h>
#include <Winder.h>

Winder::Winder(int pin1, int pin2, int pin3, int pin4){
    this->_stepper = AccelStepper(AccelStepper::FULL4WIRE, pin1, pin2, pin3, pin4);
    this->_stepper.setMaxSpeed(this->_maxSpeed); 
    this->_stepper.setAcceleration(this->_acceleration);
}

void Winder::update(){
    this->_stepper.run();

    if(!this->_stepper.isRunning()){
        if(this->_CWRotations == 0 && this->_CCWRotations == 0){
            this->_stepper.disableOutputs();
            this->_stepper.setCurrentPosition(0);
        }else if(this->_CWRotations > 0){      
            this->_stepper.move(this->_stepsPerRotation * this->_CWRotations);  
            this->_CWRotations = 0;          
        }else if(this->_CCWRotations > 0){            
            this->_stepper.move(-this->_stepsPerRotation * this->_CCWRotations);  
            this->_CCWRotations = 0;          
        }
    }
}

void Winder::addRotations(const int count){
    this->addRotations(count, Winder::RANDOM_SPLIT);
}

void Winder::addRotations(const int count, const int direction){

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
        const int CWSteps = count * factor;
        this->_CWRotations += CWSteps;   
        this->_CCWRotations += count - CWSteps;
    }
    

}