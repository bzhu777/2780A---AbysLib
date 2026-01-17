#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void progskills() { //Programming Skills

PIDDataSet TestPara{3,0.1,0.2};
    NeutralScore();
    Wing.set(true);
    Scraper.set(true);
    RunRoller(100);
    MoveEncoderPID(TestPara, 80, 21.3, 0.2, 0, true); //21 distance
    TurnMaxTimePID(TestPara, -88, 0.4, true);
    MoveTimePID(TestPara, 20, 1.5, 0.01, -88, false); // matchload 1 sec 2 v
    MoveEncoderPID(TestPara, -80, 4, 0.2, -88, true);
    TurnMaxTimePID(TestPara, -180, 0.4, true);
    MoveTimePID(TestPara, -80, 0.8, 0.2,-180, false);
    Zeroing(true,true);
    MoveEncoderPID(TestPara, 30, 0.3, 0.2, 0, true);
    TurnMaxTimePID(TestPara, -86, 0.4, true);
    MoveEncoderPID(TestPara, 90, 71, 0.2, -90, true);
    TurnMaxTimePID(TestPara, 0, 0.5, true);
    MoveTimePID(TestPara, -100, 0.5, 0.2, 0, false);
    Zeroing(true,true);
    MoveEncoderPID(TestPara, 80, 8, 0.2, 0, true);
    TurnMaxTimePID(TestPara, -88, 0.5, true);
    MoveTimePID(TestPara, -100, 0.7, 0.2, -88, false);
    HighScore();
    wait(1500,msec);
    NeutralScore();
    MoveTimePID(TestPara, 80, 1.3, 0.3, -88, false);
    wait(900,msec);
    MoveTimePID(TestPara, -100, 0.7, 0.2, -91, false); //88
    HighScore();
    wait(1500,msec);
    NeutralScore();



    MoveEncoderPID(TestPara, 80, 5.4, 0.2, -88, true);
    TurnMaxTimePID(TestPara, -176, 0.5, true);
    MoveTimePID(TestPara, -100, 3, 0.5, -179, false); //176
    Zeroing(true,true);
    MoveEncoderPID(TestPara, 80, 8, 0.2, 0, true);
    TurnMaxTimePID(TestPara, 88, 0.5, true);

    MoveTimePID(TestPara, 100, 0.7, 0.2, 88, false);
    wait(1200,msec);
    MoveTimePID(TestPara, -100, 1.2, 0.2, 88, false);
    HighScore();




//     MoveEncoderPID(TestPara, -50, 2, 0.2, 0, true);
//     TurnMaxTimePID(TestPara, 150, 0.7, true); //130
//     MoveEncoderPID(TestPara, -80, 15, 0.3, 150, true);
//     // MoveTimePID(TestPara, -80, 1.3, 0.2, 150, false);
//     TurnMaxTimePID(TestPara, 130, 1.2, false);
//  MoveTimePID(TestPara, -80, 1.3, 0.2, 130, false);

//     MiddleScore();
//     RunRoller(100);
//     wait(500, msec);

    
}