#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void SoloAWP() { //a solo autonomous win point
    PIDDataSet TestPara{2.5,0.14,0.2};
    PIDDataSet TurnPara{2.5,0.14,0.2};

    NeutralScore();
    Wing.set(true);
    Scraper.set(true);
    RunRoller(100);
    MoveEncoderPID(TestPara, 90, 24, 0.3, 0, true);
    wait(200, msec);
    TurnMaxTimePID(TurnPara, -90, 0.5, true);
    MoveTimePID(TestPara, 40, 0.7, 0.01, -90, false); // matchload
    MoveTimePID(TestPara, -90, 0.9, 0.15, -90, false); // approach goal
    HighScore();
    Scraper.set(false);
    Zeroing(true, true);
    wait(1000, msec);
    NeutralScore();

    MoveEncoderPID(TestPara, 80, 2, 0.3, 0, true); 
    TurnMaxTimePID(TurnPara, -110, 0.67, true); //0.4
    MoveEncoderPID(TestPara, 80, 19, 0.1, -115, true);
    Scraper.set(true);
    MoveEncoderPID(TestPara, 40, 5, 0.2, -90, false);
    Scraper.set(false);
    MoveEncoderPID(TestPara, 80, 29, 0.2, -90, false);
    MoveEncoderPID(TestPara, 40, 9, 0.2, -90, true);
    Scraper.set(true);
    TurnMaxTimePID(TurnPara, -48, 0.4, true);
    MoveTimePID(TestPara, -80, 0.3, 0.02, -48, false);
    MiddleScore();
    MoveTimePID(TestPara, -30, 0.2, 0.01, -48, false);


    wait(1000, msec);
    NeutralScore();
    MoveEncoderPID(TestPara, 80, 39, 0.2, -48, true);
    MoveEncoderPID(TestPara, 80, 21, 0.2, 0, true);
    MoveTimePID(TestPara, 25, 0.35, 0.01, 0, false); //matchload
    MoveTimePID(TestPara, -95, 0.7, 0.3, 0, false); //back up to the goal
    HighScore();




}