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
    MoveEncoderPID(TestPara, 80, 25, 0.2, 0, true); //Drive forward approaching matchload 1
    wait(500, msec);
    TurnMaxTimePID(TestPara, -88, 0.55, true); // turn toward matchload 1
    MoveTimePID(TestPara, 20, 1.8, 0.01, -88, false); // scrape the matchload
    wait(1500, msec);
    MoveEncoderPID(TestPara, -80, 4, 0.2, -88, true); // move back from matchload
    RunRoller(0);
    TurnMaxTimePID(TestPara, -180, 0.4, true); // turn away from the wall to prepare for wall align
    MoveTimePID(TestPara, -60, 0.8, 0.2, -180, false); // wall align
    Scraper.set(false);
    Zeroing(true,true);// first time reset
    MoveEncoderPID(TestPara, 30, 0.3, 0.2, 0, true); //forward
    TurnMaxTimePID(TestPara, -86, 0.4, true); // turn
    MoveEncoderPID(TestPara, 90, 75, 0.2, -88, false); // forward along side
    MoveEncoderPID(TestPara, 40, 3, 0.2, -88, true);
    TurnMaxTimePID(TestPara, 0, 0.5, true); // prepare for wall alignment
    MoveTimePID(TestPara, -60, 1, 0.2, -3, false); //wall alignment
    Zeroing(true,true);// second time reset
    Scraper.set(true);
    wait(700 ,msec);
    MoveEncoderPID(TestPara, 80, 10, 0.2, 0, true); //approach goal 3
    wait(500 ,msec);
    TurnMaxTimePID(TestPara, -90, 0.5, true); // turn away from goal 3
    RunRoller(100);
    wait(200, msec);
    MoveTimePID(TestPara, -100, 0.8, 0.2, -90, false); // reverse into goal 
    HighScore();// score first goal
    wait(3500,msec);
    NeutralScore();
    MoveEncoderPID(TestPara, 80, 12, 0.2, -88, false);
    MoveTimePID(TestPara, 20, 1.6, 0.01, -88, false); // matchload 3
    wait(1250, msec);
    MoveEncoderPID(TestPara, -60, 23, 0.2, -89, true);//ram into long goal
    HighScore();//score second time
    wait(3500,msec);
    NeutralScore();
    RunRoller(0);
    MoveEncoderPID(TestPara, 80, 8, 0.2, -88, true);//(3rd and 4th goal)
    TurnMaxTimePID(TestPara, -179, 0.5, true);
    MoveEncoderPID(TestPara, -100, 95, 0.2, -179, false);
    MoveTimePID(TestPara, -30, 1, 0.2, -179, false);
    Zeroing(true,true);
    MoveEncoderPID(TestPara, 80, 9, 0.2, 0, true);
    wait(300,msec);
    TurnMaxTimePID(TestPara, 88, 0.5, true);
    RunRoller(100);
    MoveTimePID(TestPara, 20, 2.5, 0.01, 88, false); 
    MoveEncoderPID(TestPara, -60, 10, 0.2, 88, true);
    RunRoller(0);
    TurnMaxTimePID(TestPara, 0, 0.7, true);
    MoveEncoderPID(TestPara, -60, 10, 0.2, 0, false);


    MoveTimePID(TestPara, -30, 1, 0.2, 0, false);
    Zeroing(true,true);// first txime reset
    MoveEncoderPID(TestPara, 30, 0.3, 0.2, 0, true);
    TurnMaxTimePID(TestPara, 86, 0.4, true);
    MoveEncoderPID(TestPara, -90, 71, 0.2, 87, true);
    TurnMaxTimePID(TestPara, 0, 0.5, true);
    MoveTimePID(TestPara, -50, 1, 0.2, 0, false);


    Zeroing(true,true);// second time reset
    MoveEncoderPID(TestPara, 80, 9, 0.2, 0, true);
    TurnMaxTimePID(TestPara, -90, 0.65, true);
    MoveTimePID(TestPara, -100, 0.8, 0.2, -90, false);
    RunRoller(100);
    HighScore();
    wait(3500,msec);
    NeutralScore();

    MoveTimePID(TestPara, 20, 3, 0.01, -88, false);
    MoveEncoderPID(TestPara, -80, 13, 0.2, -88, false);
    MoveTimePID(TestPara, -35, 0.4, 0.2, -88, false);
    HighScore();//score second time
    wait(3500,msec);
    Zeroing(true,true);
    Scraper.set(false);
    RunRoller(-100);
    MoveEncoderPID(TestPara, 100, 8, 0.2, 0, false);
    TurnMaxTimePID(TestPara, 70, 0.5, true);
    MoveTimePID(TestPara, 100, 1.5, 0.2, 70, true);
}
