#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void SoloAWP() { //a solo autonomous win point
    PIDDataSet TestPara{3,0.1,0.2};
    NeutralScore();
    Wing.set(true);
    Scraper.set(true);
    RunRoller(100);
    MoveEncoderPID(TestPara, 80, 21.3, 0.2, 0, true); //21 distance
    TurnMaxTimePID(TestPara, -88, 0.4, true);
    MoveTimePID(TestPara, 20, 0.7, 0.01, -88, false); // matchload 1 sec 2 v
    MoveTimePID(TestPara, -100, 1.13, 0.2, -96, false); // approach goal -80 heaidng -92
    wait(170, msec); //600 is original
    HighScore();
    Scraper.set(false);
    Zeroing(true, true);
    wait(1000, msec);
    NeutralScore();

    MoveEncoderPID(TestPara, 80, 1, 0.3, 0, true); 
    TurnMaxTimePID(TestPara, -110, 0.4, true); //0.4
    MoveEncoderPID(TestPara, 80, 15, 0.1, -115, true);
    Scraper.set(true);
    MoveEncoderPID(TestPara, 80, 6, 0.2, -90, true);  
    Scraper.set(false);
    MoveEncoderPID(TestPara, 80, 29, 0.2, -89, true);  
    Scraper.set(true);
    MoveEncoderPID(TestPara, 80, 6.5, 0.2, -90, true);  
    TurnMaxTimePID(TestPara, -48, 0.4, true);
    MoveTimePID(TestPara, -80, 0.17, 0.02, -48, false);
    MoveTimePID(TestPara, -30, 0.09, 0.01, -48, false);


    Zeroing(true, false);
    MiddleScore();
    RunRoller(-30);
    wait(200, msec);
    RunRoller(100);
    wait(1250, msec); //less this thingy if we run out of time //1250
    NeutralScore();
    MoveEncoderPID(TestPara, 80, 41, 0.2, -48, true);
    MoveEncoderPID(TestPara, 80, 20, 0.2, 0, true);
    MoveTimePID(TestPara, 25, 0.9, 0.01, 0, false); //matchload
    MoveTimePID(TestPara, -90, 1.1, 0.2, -3, false); //back up to the goal
    wait(400, msec);
    HighScore();




}