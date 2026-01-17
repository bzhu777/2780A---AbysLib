#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void right9block() { //right, long goal 9

    RunRoller(100);
    NeutralScore();
    MoveEncoderPID(TestPara, 80, 11, 0.2, -15, true); // drive and pick up three blocks (with scraper)
    Scraper.set(true); //lower scraper
    MoveEncoderPID(TestPara, 80, 2, 0.2, -15, true); // finish picking up the three blocks (raises scraper)
    TurnMaxTimePID(TestPara, -47, 0.5, true); // turn to the undergoal blocks
    Scraper.set(false); //raise scraper
    MoveEncoderPID(TestPara, 80, 15, 0.3, -47, true); // drive a bit to the undergoal blocks (does not pick up)
    MoveEncoderPID(TestPara, 30, 3, 0.3, -47, true); // pick up the undergoal blocks
    Scraper.set(true); //lower scraper
    MoveEncoderPID(TestPara, -80, 23, 0.2, -47, true); //drive away from the blocks
    RunRoller(0); // stop intake
    TurnMaxTimePID(TestPara, -120, 0.7, true); // turn to prep for match load
    MoveEncoderPID(TestPara, 60, 27, 0.3, -116, true); //align to the same column as the match load (-120)
    wait(100,msec);
    TurnMaxTimePID(TestPara, -170, 0.5, true); //turn to face match load
    RunRoller(100);
    MoveTimePID(TestPara, 70, 1, 0.02, -170, false); // approach match load
    wait(650, msec);
    MoveTimePID(TestPara, -70, 1, 0.2, -178, false); // go to the goal
    HighScore();
    wait(100,msec);
    RunRoller(-100);
    wait(100,msec);
    RunRoller(100);
    wait(2, sec);
    MoveEncoderPID(TestPara, 80, 2, 0.3, 180, true); //back away from goal
    MoveEncoderPID(TestPara, -100, 2, 0.3, 180, true); //hood descore
    //clamp?
}