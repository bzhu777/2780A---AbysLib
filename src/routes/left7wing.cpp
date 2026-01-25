#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"

//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void left7wing() { //left, long goal 7, with wing
    PIDDataSet TestPara{2.5,0.14,0.2};

    RunRoller(100);
    MoveEncoderPID(TestPara, 80, 3, 0.2, 0, false);
    MoveEncoderPID(TestPara, 80, 10, 0.2, 20, false);
    Scraper.set(true);
    MoveEncoderPID(TestPara, 30, 5, 0.2, 20, true);
    wait(230, msec);
    TurnMaxTimePID(TestPara, 130, 0.7, true);
    
    MoveEncoderPID(TestPara, 80, 21, 0.3, 130, false);
    MoveEncoderPID(TestPara, 80, 5, 0.3, 173, true);
    MoveTimePID(TestPara, 45, 0.8, 0.2, 173, false);
    MoveTimePID(TestPara, -90, 0.8, 0.2, 177, false);
    HighScore();
    MoveTimePID(TestPara, -30, 0.3, 0.2, 173, false);
    Zeroing(true, true);
    wait(3000, msec);
    Scraper.set(false);
    RunRoller(0);
    MoveEncoderPID(TestPara, 30, 15, 0.1, 35, true);
    MoveEncoderPID(TestPara, -55, 20, 0.2, 0, true);


    
}