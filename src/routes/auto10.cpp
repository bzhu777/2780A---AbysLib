#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"

//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void auto10() { //left, long goal 7, with wing
    PIDDataSet TestPara{2.5,0.14,0.2};

    


    
}