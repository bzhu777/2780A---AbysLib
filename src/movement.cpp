#include "vex.h"

#include "math.h"
#include "screen_gui.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"
#include "pid.hpp"

#include <iostream>

using namespace vex;

// IMPORTANT!
// +X is more to the side
// +Y is forward
// +HDG is clockwise

int turninverse=-1;//change this to -1 if turning is inversed

int JB;
int PB;
int PX;
int JX;

float RealTagHeight = 5.0; //in inches
float RealTagWidth = 5.0; //in inches
float focalLength = 200.0; 

//General Sect;
//This section includes all general codes for drive and auto


/** Resets the robot's drive train and inertial sensor
 * 
 * @param dist the distance on the motor encoders
 * @param HDG the heading on the gyro
 */
void Zeroing(bool dist, bool HDG)
{
  if(dist){
  LF.resetPosition();
  LM.resetPosition();
  LB.resetPosition();
  RF.resetPosition();
  RM.resetPosition();
  RB.resetPosition();
  }
  if(HDG){
    Gyro.setHeading(0,degrees);
  }
}

void aprilTagReset(double TARGET_ID)
{
  Resetter.takeSnapshot(aivision::ALL_TAGS);
  for (int i = 0; i < Resetter.objectCount; i++) {
    if (Resetter.objects[i].exists && Resetter.objects[i].id == TARGET_ID)
    {
      double LocateX = Resetter.objects[i].centerX;
      double LocateY = Resetter.objects[i].centerY;
      double picAngle = Resetter.objects[i].angle;
      double height = Resetter.objects[i].height;
      double width = Resetter.objects[i].width;

      double distance = (RealTagHeight * focalLength / height + RealTagWidth * focalLength / width) / 2.0;
    }
  }


  }
  

ChassisDataSet ChassisUpdate()
{
  ChassisDataSet CDS;
  CDS.Left=get_dist_travelled((LF.position(degrees)+LM.position(degrees)+LB.position(degrees))/3.0);
  CDS.Right=get_dist_travelled((RF.position(degrees)+RM.position(degrees)+RB.position(degrees))/3.0);
  CDS.Avg=(CDS.Left+CDS.Right)/2.0;
  CDS.Diff=(CDS.Right-CDS.Left);
  CDS.HDG=Gyro.heading(degrees);

  return CDS;
}

void Move(int left, int right)
{
LF.setMaxTorque(100,percent);
LM.setMaxTorque(100,percent);
LB.setMaxTorque(100,percent);
RF.setMaxTorque(100,percent);
RM.setMaxTorque(100,percent);
RB.setMaxTorque(100,percent);

LF.spin(forward,(double)left/100.0*11,volt);
LM.spin(forward,(double)left/100.0*11,volt);
LB.spin(forward,(double)left/100.0*11,volt);
RF.spin(forward,(double)right/100.0*11,volt);
RM.spin(forward,(double)right/100.0*11,volt);
RB.spin(forward,(double)right/100.0*11,volt);
}

void SlowMove(int left, int right, int speed)
{
LF.setMaxTorque(speed,percent);
LM.setMaxTorque(speed,percent);
LB.setMaxTorque(speed,percent);
RF.setMaxTorque(speed,percent);
RM.setMaxTorque(speed,percent);
RB.setMaxTorque(speed,percent);

LF.spin(forward,(double)left/100.0*11,volt);
LM.spin(forward,(double)left/100.0*11,volt);
LB.spin(forward,(double)left/100.0*11,volt);
RF.spin(forward,(double)right/100.0*11,volt);
RM.spin(forward,(double)right/100.0*11,volt);
RB.spin(forward,(double)right/100.0*11,volt);
}

void BStop()
{
LF.setStopping(brake);
LM.setStopping(brake);
LB.setStopping(brake);
RF.setStopping(brake);
RM.setStopping(brake);
RB.setStopping(brake);

LF.stop();
LM.stop();
LB.stop();
RF.stop();
RM.stop();
RB.stop();
}

void CStop()
{
LF.setStopping(coast);
LM.setStopping(coast);
LB.setStopping(coast);
RF.setStopping(coast);
RM.setStopping(coast);
RB.setStopping(coast);

LF.stop();
LM.stop();
LB.stop();
RF.stop();
RM.stop();
RB.stop();
}

void RunRoller(int val)
{
Intake1.setMaxTorque(100,percent);
Intake1.spin(forward,(double)val/100.0*12,volt);
}

void RunChainbar(int val)
{
ChainBar.setMaxTorque(100,percent);
ChainBar.spin(forward,(double)val/100.0*12,volt);
}

void SpinLift(int val)
{
  const int maxLiftDegrees = 1700;
  int currentPosition = static_cast<int>(round(Lift.position(degrees)));

  if (val > 0 && currentPosition >= maxLiftDegrees) {
    Lift.stop();
    return;
  }

  Lift.setMaxTorque(100,percent);
  Lift.spin(forward,(double)val/100.0*12,volt);
}


