#include "screen_gui.hpp"
#include "vex.h"
#include "movement.hpp"

void DisplayAutoSelector(void)
{

  Brain.Screen.clearScreen();

//auton selector
Brain.Screen.setFont(monoM);
Brain.Screen.setFillColor(black);
Brain.Screen.setCursor(1,1);
Brain.Screen.setPenWidth(3);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(1,25,100,50);

Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(375,25,100,50);

Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(1,100,100,50);

Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(375,100,100,50);

Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(1,175,100,50);

Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(375,175,100,50);

Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(187,5,100,50);

Brain.Screen.setPenColor("#84fffd");
Brain.Screen.drawRectangle(187,175,100,50);
}

void DisplayWords(void)
{
  Brain.Screen.setPenColor("#84fffd");
  Brain.Screen.setFont(monoM);
  Brain.Screen.setCursor(3,3);
  Brain.Screen.print("Left 7");

  Brain.Screen.setCursor(7,3);
  Brain.Screen.print("Left34");

    Brain.Screen.setCursor(11,3);
  Brain.Screen.print("ODOM TEST");

    Brain.Screen.setCursor(3,40);
  Brain.Screen.print("Right 9");

  Brain.Screen.setCursor(7,40);
  Brain.Screen.print("Right36");

    Brain.Screen.setCursor(11,40);
  Brain.Screen.print("SAWP");

  Brain.Screen.setCursor(11,22);
  Brain.Screen.print("Skills");
}

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
int AutoSelectorVal;

void UpdateDynamic(void)
{
  DisplayAutoSelector();
  DisplayWords();
  Brain.Screen.setFillColor("#84fffd");
  Brain.Screen.setPenColor(black);

if(AutoSelectorVal==1){
  Brain.Screen.drawRectangle(1,25,100,50);
  Brain.Screen.setCursor(3,3);
  Brain.Screen.print("Left 9");

  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor("#84fffd");
  Brain.Screen.setCursor(3,10);
  Brain.Screen.print("LEFT SIDE");
  Brain.Screen.setCursor(4,10);
  Brain.Screen.print("7 WING");
  Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==2){
  Brain.Screen.drawRectangle(375,25,100,50);
  Brain.Screen.setCursor(3,40);
  Brain.Screen.print("Right 9");

  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor("#84fffd");
  Brain.Screen.setCursor(3,10);
  Brain.Screen.print("RIGHT SIDE");
  Brain.Screen.setCursor(4,10);
  Brain.Screen.print("9 BLOCK");
  Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#84fffd");
}

if(AutoSelectorVal==3){
  Brain.Screen.drawRectangle(1,100,100,50);
  Brain.Screen.setCursor(7,3);
  Brain.Screen.print("Left36");

Brain.Screen.setFillColor(black);

    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("LEFT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("34 WING");
Brain.Screen.setFont(monoM);  
  Brain.Screen.setFillColor("#84fffd");
}

if(AutoSelectorVal==4){
Brain.Screen.drawRectangle(375,100,100,50);
  Brain.Screen.setCursor(7,40);
  Brain.Screen.print("RIGHT36");

Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("RIGHT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("9 BLOCK");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==5){
  Brain.Screen.drawRectangle(1,175,100,50);
      Brain.Screen.setCursor(11,3);
  Brain.Screen.print("GOAL CLAMP");

Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("ODOM TEST");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("POSITION UPDATE");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==6){
Brain.Screen.drawRectangle(375,175,175,50);
Brain.Screen.setCursor(11,40);
Brain.Screen.print("SAWP");
Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("BOTH SIDES");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("AWP");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

  }

if(AutoSelectorVal==7){
  Brain.Screen.drawRectangle(187,175,100,50);
  Brain.Screen.setCursor(11,22);
  Brain.Screen.print("Skills");

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

}

int OdomPosScreen()
{
  while(true)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(monoM);
    Brain.Screen.setCursor(1,2);
    Brain.Screen.setPenColor("#84fffd");
    Brain.Screen.print("X: %.2f in",Xpos);
    Brain.Screen.setCursor(3,2);
    Brain.Screen.setPenColor("#84fffd");
    Brain.Screen.print("Y: %.2f in",Ypos);
    Brain.Screen.setCursor(5,2);
    Brain.Screen.setPenColor("#84fffd");
    Brain.Screen.print("HDG: %.2f deg",Gyro.heading(degrees));

    Brain.Screen.drawLine(6,1,6,20);
    Brain.Screen.drawLine(1,15,5,15);
    Brain.Screen.drawLine(1,30,5,30);

    Brain.Screen.setCursor(8,1);
    Brain.Screen.print("Battery Percent: %d %%",Brain.Battery.capacity(percent));
    Brain.Screen.setCursor(10,1);
    Brain.Screen.print("Battery Voltage: %.2f V",Brain.Battery.voltage());
    Brain.Screen.setCursor(1,7);
    double avgIntake = (Intake1.temperature(celsius)+Intake2.temperature(celsius))/2;
    Brain.Screen.print("Intake Temp: %.2f C",avgIntake);
    double avgDrive = (LF.temperature(celsius)+LM.temperature(celsius)+LB.temperature(celsius)+RF.temperature(celsius)+RM.temperature(celsius)+RB.temperature(celsius))/6;
    Brain.Screen.setCursor(3,7);
    Brain.Screen.print("Drive Temp: %.2f C",avgDrive);
    Brain.Screen.setCursor(5,7);
    

  }
  return 0;
}