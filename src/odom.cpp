#include "vex.h"

#include "math.h"
#include "screen_gui.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

#include <iostream>

using namespace vex;

// IMPORTANT!
// +X is more to the side
// +Y is forward
// +HDG is clockwise

//ODOM VARIABLES

double Xpos=0;
double Ypos=0;
double prevTrackingFrontLeft=0;
double prevTrackingFrontRight=0;
double prevTrackingSide=0;
double prevHDG=0;
double HDG=0;
double prevX=0;
double prevY=0;


/** Sets the position to 0 */
void OdomZeroing() {
  SetPos(0,0,0);
}

/** Sets the position
 * @param X the wanted x position to set to
 * @param Y the wanted y position to set to
 * @param HDG the wanted heading to set to
 */
void SetPos(double X, double Y, double HDG)
{
  odomUpdate=false;
  Xpos=X;
  Ypos=Y;
  prevHDG = HDG;
  xROdom.resetPosition();
  xLOdom.resetPosition();
  yOdom.resetPosition();
  OdomDataSet ODS = OdomUpdate();
  prevTrackingFrontLeft = ODS.CurrTrackingFrontLeft;
  prevTrackingFrontRight = ODS.CurrTrackingFrontRight;
  prevTrackingSide  = ODS.CurrTrackingSide;
  odomUpdate=true;
}


void UpdatePos(void) {
  OdomDeltaSet movement = OdomGetDistTravelled();
  double dFL = movement.DeltaTrackingFrontLeft;
  double dFR = movement.DeltaTrackingFrontRight;
  double dS = movement.DeltaTrackingSide;

  double Theta = (dFL-dFR) / (RightOdomFrontOffset + LeftOdomFrontOffset);
  double ABSorientation = (Theta*180/M_PI) + prevHDG;

  double MovementAVG = (dFL + dFR) / 2.0;
  double OffsetAVG = (LeftOdomFrontOffset + RightOdomFrontOffset) / 2.0;
  double OrientationAVG = (prevHDG + Theta/2);
  double DisplacementX;
  double DisplacementY;

  if (Theta == 0)
  {
    DisplacementX = dS;
    DisplacementY = MovementAVG;
  }
  else
  {
    DisplacementX = 2 * sin(Theta/2) * (dS / Theta + OdomSideOffset);
    DisplacementY = 2 * sin(Theta/2) * (MovementAVG / Theta + OffsetAVG);
  }

  double r = sqrt(DisplacementX*DisplacementX + DisplacementY*DisplacementY);
  double robotAngle = atan2(DisplacementY, DisplacementX);
  double angleOffset = robotAngle - OrientationAVG;
  double DisplacementABS[2] = {r * cos(angleOffset), r * sin(angleOffset)};

  Xpos = prevX + DisplacementABS[0];
  Ypos = prevY + DisplacementABS[1];

  prevHDG = ABSorientation;
  prevX = Xpos;
  prevY = Ypos;
}



OdomDataSet OdomUpdate()
{
  OdomDataSet ODS;
  ODS.CurrTrackingFrontLeft=get_odom_dist_travelled(xLOdom.position(degrees));
  ODS.CurrTrackingFrontRight=get_odom_dist_travelled(xROdom.position(degrees));
  ODS.CurrTrackingSide=get_odom_dist_travelled(yOdom.position(degrees));
  return ODS;
}

OdomDeltaSet OdomGetDistTravelled()
{
  OdomDataSet ODS=OdomUpdate();
  OdomDeltaSet movement;
  movement.DeltaTrackingFrontLeft=ODS.CurrTrackingFrontLeft-prevTrackingFrontLeft;
  movement.DeltaTrackingFrontRight=ODS.CurrTrackingFrontRight-prevTrackingFrontRight;
  movement.DeltaTrackingSide=ODS.CurrTrackingSide-prevTrackingSide;
  prevTrackingSide=ODS.CurrTrackingSide;
  prevTrackingFrontLeft=ODS.CurrTrackingFrontLeft;
  prevTrackingFrontRight=ODS.CurrTrackingFrontRight;

  return movement;
}

void TurnToAngle(PIDDataSet KVals,double DeltaAngle,double TE, bool brake){
  double CSpeed=0;
  double PVal=0;
  double IVal=0;
  double DVal=0; 
  double LGV=0;
  PrevE=0;
  double Correction=0;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
    LGV = DeltaAngle - ABSorientation;
    if(LGV>180) LGV=LGV-360;
    PVal=KVals.kp*LGV;
    IVal=IVal+KVals.ki*LGV*0.02;
    DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;

  Move(CSpeed-Correction,CSpeed+Correction);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(180,msec);}
  else CStop();
}

void TurnToPoint(PIDDataSet KVals,double Xval, double Yval,double TE, bool brake){
  double TargetAngle = atan2(Yval-Ypos, Xval-Xpos) * 180 / M_PI;
  double CSpeed=0;
  double PVal=0;
  double IVal=0;
  double DVal=0; 
  double LGV=0;
  PrevE=0;
  double Correction=0;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
    LGV = TargetAngle - ABSorientation;
    if(LGV>180) LGV=LGV-360;
    PVal=KVals.kp*LGV;
    IVal=IVal+KVals.ki*LGV*0.02;
    DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;

  Move(CSpeed-Correction,CSpeed+Correction);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(180,msec);}
  else CStop();
}