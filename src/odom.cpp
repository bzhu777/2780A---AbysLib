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

float Xpos=0;
float Ypos=0;
float prevTrackingFrontLeft=0;
float prevTrackingFrontRight=0;
float prevTrackingSide=0;
float prevHDG=0;
float HDG=0;
float prevX=0;
float prevY=0;
float ABSorientation=0;

const float invTrackWidth = 1.0 / (RightOdomFrontOffset + LeftOdomFrontOffset);
const float OffsetAVG = (LeftOdomFrontOffset + RightOdomFrontOffset) * 0.5;


/** Sets the position
 * @param X the wanted x position to set to
 * @param Y the wanted y position to set to
 * @param HDG the wanted heading to set to
 */
void SetPos(float X, float Y, float HDG)
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

/** Sets the position to 0 */
void OdomZeroing() {
  SetPos(0,0,0);
}

void UpdatePos(void) {
  OdomDeltaSet movement = OdomGetDistTravelled();

  float dFL = movement.DeltaTrackingFrontLeft;
  float dFR = movement.DeltaTrackingFrontRight;
  float dS  = movement.DeltaTrackingSide;


  float Theta = (dFL - dFR) * invTrackWidth;
  float ABSorientation = prevHDG + Theta * 57.29577951308232; // Convert to degrees


  float MovementAVG = (dFL + dFR) * 0.5;
  float OrientationAVG = prevHDG + Theta * 0.5;

  float DisplacementX;
  float DisplacementY;

if (fabs(Theta) < 1e-5)
{
    DisplacementX = dS;
    DisplacementY = MovementAVG;
}
else
{
    float halfTheta = Theta * 0.5;
    float sinHalfTheta = sin(halfTheta);
    float commonFactor = (2.0 * sinHalfTheta) / Theta;

    DisplacementX = commonFactor * (dS + Theta * OdomSideOffset);
    DisplacementY = commonFactor * (MovementAVG + Theta * OffsetAVG);
}

float cosO = cos(OrientationAVG);
float sinO = sin(OrientationAVG);

float globalX = DisplacementX * cosO - DisplacementY * sinO;
float globalY = DisplacementX * sinO + DisplacementY * cosO;

Xpos = prevX + globalX;
Ypos = prevY + globalY;

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

