#include "../movement.hpp"
#include "../helper_functions.hpp"
#include "vex.h"
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

void left34wing() { //left, long goal 3, mid goal 4, with wing

    PIDDataSet TestPara{2.5,0.14,0.2};

    RunRoller(100);
    MoveEncoderPID(TestPara, 80, 3, 0.2, 0, false);
    MoveEncoderPID(TestPara, 80, 10, 0.2, 20, false);
    Scraper.set(true);
    MoveEncoderPID(TestPara, 30, 6, 0.2, 20, true);
    wait(250, msec);
    TurnMaxTimePID(TestPara, 136, 0.8, true);
    MoveEncoderPID(TestPara, -80, 10, 0.3, 140, false);
    MoveTimePID(TestPara, -30, 0.4, 0.1, 140, false);
    MiddleScore();
    wait(1575, msec);
    RunRoller(-50);
    NeutralScore();
    MoveEncoderPID(TestPara, 85, 40, 0.3, 130, true);
    RunRoller(100);
    TurnMaxTimePID(TestPara, 175, 0.5, true);
    MoveEncoderPID(TestPara, 70, 6, 0.4, 175, false);
    MoveTimePID(TestPara, 35, 0.55, 0.1, 170, false);
    MoveTimePID(TestPara, -75, 0.76, 0.3, 178, false);
    HighScore();
    MoveTimePID(TestPara, -40, 0.23, 0.3, 178, false);
    Zeroing(true, true);
    wait(1750, msec);
    Scraper.set(false);
    RunRoller(0);
    MoveEncoderPID(TestPara, 50, 18, 0.1, 35, true);
    MoveEncoderPID(TestPara, -75, 23, 0.2, 0, true);


    // RunRoller(100);
    // NeutralScore();
    // MoveEncoderPID(TestPara, 80, 14, 0.2, 15, true); // drive and pick up three blocks (with scraper)
    // Scraper.set(true); //lower scraper
    // MoveEncoderPID(TestPara, 80, 2, 0.2, 15, true);;
    // TurnMaxTimePID(TestPara, 135, 0.5, true); // turn to the undergoal blocks
    // MoveTimePID(TestPara, -80, 0.7, 0.3, 135, true); // drive a bit to the undergoal blocks (does not pick up)
    // RunRoller(0);
    // wait(100,msec);
    // RunRoller(80);
    // MiddleScore();
    // wait(500,msec);
    // NeutralScore();
    // MoveEncoderPID(TestPara, 90, 42, 0.3, 130, true); //drive angled towards the match load //39
    // RunRoller(0);
    // TurnMaxTimePID(TestPara, 172, 0.3, true); //turn to face match load

    // RunRoller(100);
    // Scraper.set(true);
    // MoveTimePID(TestPara, 80, 1, 0.02, 172, false); // approach match load
    // wait(700, msec);
    // MoveTimePID(TestPara, -80, 1, 0.2, 172, false); // go to the goal 172
    // HighScore();
    // wait(100,msec);
    // RunRoller(-100);
    // wait(100,msec);
    // RunRoller(100);
    // wait(2, sec);
    // MoveEncoderPID(TestPara, 80, 2, 0.3, 172, true); //back away from goal
    // // TurnMaxTimePID(TestPara, -45, 0.5, true); //turn to face hood
    // // MoveEncoderPID(TestPara, -100, 7, 0.3, -45, false); //hood descore




}