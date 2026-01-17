/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//#include "STDLib.cpp"
#include "vex.h"

#include "screen_gui.hpp"
#include "movement.hpp"
#include "routes/routes.hpp"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

bool SP;
bool EXIT;
void pre_auton(void) {
   EXIT=true; // change to "FALSE" for everything else
  PX=0;
  JX=0;
  AutoSelectorVal=7; // change to 0 for everything else
  SP=false;
  Scraper.set(false);
  Wing.set(false);
  NeutralScore();
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
Gyro.calibrate();

//Ensure Robot Launch Position is set before auto proceeds, once plugged into field control,
//start program and do not temper bot under all circumstances

//1. IF ANY ADJUSTMENT IS NEEDED, QUIT PROGRAM, THEN ADJUST, RESTART PROGRAM AFTER ADJUSTMENTS COMPLETED
//2. DO NOT START PROGRAM BEFORE PLUGGING IN FIELD CONTROL, THIS MAY DISABLE AUTO
//3. ONLY SIGNAL REFEREES TO BEGIN MATCH AFTER THE ZEROING PROMPT ON SCREEN HAS CLEARED

//Print precautionary message
Brain.Screen.drawRectangle(0,0,500,500);

Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(2,10);
Brain.Screen.print("FLIR TIMEOUT");


waitUntil(!Gyro.isCalibrating());


Zeroing(true,true);
DisplayAutoSelector();
DisplayWords();

//task AutoSelTask=task(ScreenSelMain);
  while(!EXIT)
{
if(Brain.Screen.xPosition()<100)
{
if(Brain.Screen.yPosition()<75&&Brain.Screen.yPosition()>25)AutoSelectorVal=1;
else if(Brain.Screen.yPosition()<150&&Brain.Screen.yPosition()>100)AutoSelectorVal=3;
else if(Brain.Screen.yPosition()<225&&Brain.Screen.yPosition()>175)AutoSelectorVal=5;
}
else if(Brain.Screen.xPosition()>375)
{
if(Brain.Screen.yPosition()<75&&Brain.Screen.yPosition()>25)AutoSelectorVal=2;
else if(Brain.Screen.yPosition()<150&&Brain.Screen.yPosition()>100)AutoSelectorVal=4;
else if(Brain.Screen.yPosition()<225&&Brain.Screen.yPosition()>175)AutoSelectorVal=6;
}

if(Brain.Screen.xPosition()>187&&Brain.Screen.xPosition()<287)
{
if(Brain.Screen.yPosition()<55&&Brain.Screen.yPosition()>5) EXIT=true;
else if(Brain.Screen.yPosition()>125&&Brain.Screen.yPosition()<225)AutoSelectorVal=7;
}

if(Brain.Screen.pressing()&&!SP) UpdateDynamic();

SP=Brain.Screen.pressing();

}

Brain.Screen.clearScreen();
if(AutoSelectorVal==1){
  Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("LEFT");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("9BLOCK");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==2){
Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("Right");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("9BLOCK");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#84fffd");
}

if(AutoSelectorVal==3){

Brain.Screen.setFillColor(black);

    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("Left");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("36BLOCK");
Brain.Screen.setFont(monoM);  
  Brain.Screen.setFillColor("#84fffd");
}

if(AutoSelectorVal==4){

Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("Right");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("36BLOCK");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==5){

Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("LEFT");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("Goal Clamp");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==6){
  
  Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("Solo");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("AWP");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

  }

if(AutoSelectorVal==7){

Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("SKILLS");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("SKILLS");
Brain.Screen.setFont(monoM); 
Brain.Screen.setFillColor("#84fffd");

}

Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(5,10);
Brain.Screen.print("AUTO CONFIRMED");



  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  
//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

//Do not change the below
Zeroing(true,true);
//can start editing if necessary
//Put Auto route function into if statements to use autoselector
if(AutoSelectorVal==1)// left, long goal 9
{
  left9block();
}

if(AutoSelectorVal==2)// right, 9 long goal
{
  right9block();

}

if(AutoSelectorVal==3)// left, 6 long goal, 3 mid goal
{
  left36block();
} 

if(AutoSelectorVal==4)// right, 6 long goal, 3 mid goal
{
  right36block();
}

if(AutoSelectorVal==5)// empty
{
   //test();
}


if(AutoSelectorVal==6)//SAWP
{
  SoloAWP();
}


if(AutoSelectorVal==7)//prog skills
{ 
  progskills();

}
//MoveTimePID(TestPara, -100, 0.5,0.1,-40,true);
//(PID Parameters, motor speed -100 - 100, time for travel 0 - inf, time to accelerate to full speed, Absolute Heading, Braking?)

    // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
CStop();
}
int RV;
int LV;

//------------------------------------------------------------------------ SPLIT ARCADE DRIVE
int DriveTask(void){
  while(true)
  {
    int DeadBand = 15;

    EXIT=true;
    RV=-Controller1.Axis3.position(percent)+Controller1.Axis1.position(percent);
    LV=-Controller1.Axis3.position(percent)-Controller1.Axis1.position(percent);

    if (abs(LV) < DeadBand) LV = 0;
    if (abs(RV) < DeadBand) RV = 0;

    Move(LV,RV);
  }

return 0;
}
int V;

//------------------------------------------------------------------------ REDIRECT MECH CONTROL
int ATask(void)
{
  if (Controller1.ButtonR2.pressing()==1)
    {
      RunRoller(100);
      MiddleScore();
    }
    else if (Controller1.ButtonL2.pressing()==1)
    {
      RunRoller(-100);
      NeutralScore();
    }
    else if (Controller1.ButtonR1.pressing()==1)
    {
      RunRoller(100); 
      HighScore();
    }
    else if (Controller1.ButtonL1.pressing()==1) 
    {
      RunRoller(100);
      NeutralScore();
    }
    else if (Controller1.ButtonUp.pressing()==1)
    {
      RunRoller(50);
      MiddleScore();
    }
    else
    {
      RunRoller(0);
    }
  return 0;
}

int ButtonPressingDown,DownTaskActiv;
int ButtonPressingB,BTaskActiv;

int PTask(void)
{
    while(true)
    {
      //---------------------------------------------------------------------- SCRAPER CONTROL
    if(DownTaskActiv==0&&Controller1.ButtonDown.pressing()&&ButtonPressingDown==0)
    {
      ButtonPressingDown=1;
      DownTaskActiv=1;
      Wing.set(true);
    }

    else if(!Controller1.ButtonDown.pressing())ButtonPressingDown=0;

    else if(DownTaskActiv==1&&Controller1.ButtonDown.pressing()&&ButtonPressingDown==0)
    {
      ButtonPressingDown=1;
      DownTaskActiv=0;
      Wing.set(false);
    }
    //------------------------------------------------------------------------ WING CONTROL
    if(BTaskActiv==0&&Controller1.ButtonB.pressing()&&ButtonPressingB==0)
    {
      ButtonPressingB=1;
      BTaskActiv=1;
      Scraper.set(true);
    }
    else if(!Controller1.ButtonB.pressing())ButtonPressingB=0;

    else if(BTaskActiv==1&&Controller1.ButtonB.pressing()&&ButtonPressingB==0)
    {
      ButtonPressingB=1;
      BTaskActiv=0;
      Scraper.set(false);
    }
    

    

  }
  return 0;
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  EXIT=true;//Force Exit Autosel once drivercontrol began.
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    
    
    
    task Dtask=task(DriveTask);
    task Atask=task(ATask);
    task Ptask=task(PTask);
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//


int main() {
  
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  
  

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
  
