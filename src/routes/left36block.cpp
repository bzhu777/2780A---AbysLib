#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void left36block() { //left, long goal 6, mid goal 3

    RunRoller(100);
    NeutralScore();
    MoveEncoderPID(TestPara, 80, 14, 0.2, 15, true); // drive and pick up three blocks (with scraper)
    Scraper.set(true); //lower scraper
    MoveEncoderPID(TestPara, 80, 2, 0.2, 15, true);;
    TurnMaxTimePID(TestPara, 135, 0.5, true); // turn to the undergoal blocks
    MoveTimePID(TestPara, -80, 0.7, 0.3, 135, true); // drive a bit to the undergoal blocks (does not pick up)
    RunRoller(0);
    wait(100,msec);
    RunRoller(80);
    MiddleScore();
    wait(500,msec);
    NeutralScore();
    MoveEncoderPID(TestPara, 90, 42, 0.3, 130, true); //drive angled towards the match load //39
    RunRoller(0);
    TurnMaxTimePID(TestPara, 172, 0.3, true); //turn to face match load

    RunRoller(100);
    Scraper.set(true);
    MoveTimePID(TestPara, 80, 1, 0.02, 172, false); // approach match load
    wait(700, msec);
    MoveTimePID(TestPara, -80, 1, 0.2, 172, false); // go to the goal 172
    HighScore();
    wait(100,msec);
    RunRoller(-100);
    wait(100,msec);
    RunRoller(100);
    wait(2, sec);
    MoveEncoderPID(TestPara, 80, 2, 0.3, 172, true); //back away from goal
    // TurnMaxTimePID(TestPara, -45, 0.5, true); //turn to face hood
    // MoveEncoderPID(TestPara, -100, 7, 0.3, -45, false); //hood descore




}