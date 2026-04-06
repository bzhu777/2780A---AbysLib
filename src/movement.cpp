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

int turninverse=-1;//change this to -1 if turning is inversed

int JB;
int PB;
int PX;
int JX;

//ODOM VARIABLES

double Xpos=0;
double Ypos=0;
double prevTrackingFront=0;
double prevTrackingSide=0;
double prevHDGpos=0;
double ThetaDeg=0;

PIDDataSet TestPara{3,0.1,0.2};


//tune p value if robot is aggresively correcting itself


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
  Gyro.setRotation(HDG, degrees);
  prevHDGpos = HDG;
  xOdom.resetPosition();
  yOdom.resetPosition();
  OdomDataSet ODS = OdomUpdate();
  prevTrackingFront = ODS.CurrTrackingFront;
  prevTrackingSide  = ODS.CurrTrackingSide;
  odomUpdate=true;
}

/* gets the gyro rotation in degrees */
double getGyroDeg()
{
  return Gyro.rotation(degrees);
}

void UpdatePos(void) {
  OdomDeltaSet movement = OdomGetDistTravelled();
  double dF = movement.DeltaTrackingFront; // stores some values from the sensor into local variables
  double dS = movement.DeltaTrackingSide;
  double HDG = Gyro.rotation(degrees);

  double dThetaDeg = HDG - prevHDGpos; // this is bascially how much the robot turned since last update

  //convert to radians
  double dThetaRad = dThetaDeg * M_PI / 180.0;

  dF -= OdomFrontOffset * dThetaRad; // offset correction
  dS -= OdomSideOffset  * dThetaRad;

  // average heading during the movement
  double ThetaMidRad = (prevHDGpos + dThetaDeg / 2.0) * M_PI / 180.0;

  double dX = dS * cos(ThetaMidRad) - dF * sin(ThetaMidRad);
  double dY = dS * sin(ThetaMidRad) + dF * cos(ThetaMidRad);
  

  Xpos += dX; // update global position
  Ypos += dY;
  prevHDGpos = HDG;

  std::cout <<(Intake1.temperature(celsius) + Intake2.temperature(celsius))/2.0 << std::endl;
  //std::cout << "X: " << Xpos << " Y: " << Ypos << " HDG: " << HDG << std::endl; // print x and y for testing
}

OdomDataSet OdomUpdate()
{
  OdomDataSet ODS;
  ODS.CurrTrackingFront=get_odom_dist_travelled(xOdom.position(degrees));
  ODS.CurrTrackingSide=get_odom_dist_travelled(yOdom.position(degrees));
  return ODS;
}

OdomDeltaSet OdomGetDistTravelled()
{
  OdomDataSet ODS=OdomUpdate();
  OdomDeltaSet movement;
  ChassisDataSet CDS;
  movement.DeltaTrackingSide=ODS.CurrTrackingSide-prevTrackingSide;
  prevTrackingSide=ODS.CurrTrackingSide;
  return movement;
}

// void TurnToAnglePID(PIDDataSet KVals,double DeltaAngle,double TE, bool brake){
//   double CSpeed=0;

//   double PVal=0;
//   double IVal=0;
//   double DVal=0; 
//   double LGV=0;
//   PrevE=0;
//   double Correction=0;
//   Brain.Timer.reset();

//   while(Brain.Timer.value() <= TE)
//   {
  
//   wait(20, msec);
//   }
//   if(brake){BStop();
//   wait(180,msec);}
//   else CStop();
// }

//--------------------------------------------------------------------------PID FUNCTIONS


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
Intake2.setMaxTorque(100,percent);
Intake1.spin(forward,(double)val/100.0*12,volt);
Intake2.spin(forward,(double)val/100.0*12, volt);
}

void MiddleScore()
{
  Redirect1.set(false);
}
void NeutralScore()
{
  Redirect1.set(false);
}
void HighScore()
{
  Redirect1.set(true);
}

int PrevE;//Error at t-1

/** Moves the robot forward or backward
 * @param KVals the PID constants
 * @param Speed the speed, from -100 to 100
 * @param dist distance travelled, in inches
 * @param AccT time to max speed (s)
 * @param ABSHDG absolute heading of the robot
 * @param brake Brake at end, or coast
 */
void MoveEncoderPID(PIDDataSet KVals, int Speed, double dist,double AccT, double ABSHDG,bool brake){
  Speed = Speed*-1;
  double CSpeed=0;
  Zeroing(true,false);
  ChassisDataSet SensorVals;
  SensorVals=ChassisUpdate();
  double PVal=0;
  double IVal=0;
  double DVal=0;
  double LGV=0;//define local gyro variable.
  PrevE=0;
  double Correction=0;
  Brain.Screen.clearScreen();

  while(fabs(SensorVals.Avg) <= fabs(dist))
  {
    //std::cout << SensorVals.Avg << " " << dist << std::endl;
if(fabs(CSpeed)<fabs((double)Speed))
{
  CSpeed+=Speed/AccT*0.02;
}

  SensorVals=ChassisUpdate();
  LGV=SensorVals.HDG-ABSHDG;
  if(LGV>180) LGV=LGV-360;
  PVal=KVals.kp*LGV;
  IVal=IVal+KVals.ki*LGV*0.02;
  DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;

  Move(CSpeed-Correction,CSpeed+Correction);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){
    BStop();
    wait(120,msec);
  }
  else CStop();
}

/** Moves the robot forward or backward. Negative speed moves
 * the robot forward. Positive value moves it backward. (Ik it's fucked up)
 * @param KVals the PID constants
 * @param DeltaAngle the absolute heading to turn to
 * @param TE time to calculate turn (not time to turn)
 * @param brake Brake at end, or coast
 */
void TurnMaxTimePID(PIDDataSet KVals,double DeltaAngle,double TE, bool brake){
  double CSpeed=0;
  Zeroing(true,false);
  ChassisDataSet SensorVals;
  SensorVals=ChassisUpdate();
  double PVal=0;
  double IVal=0;
  double DVal=0; 
  double LGV=0;
  PrevE=0;
  double Correction=0;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
  SensorVals=ChassisUpdate();
  LGV=SensorVals.HDG-DeltaAngle;
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

/** Moves the robot forward or backward. Negative speed moves
 * the robot forward. Positive value moves it backward. (Ik it's fucked up)
 * @param KVals the PID constants
 * @param DeltaAngle the absolute heading to turn to
 * @param TE time to calculate turn (not time to turn)
 * @param brake Brake at end, or coast
 */
void SpeedTurnMaxTimePID(PIDDataSet KVals,double DeltaAngle,double TE, double Speed, bool brake){
  double CSpeed=0;
  Zeroing(true,false);
  ChassisDataSet SensorVals;
  SensorVals=ChassisUpdate();
  double PVal=0;
  double IVal=0;
  double DVal=0; 
  double LGV=0;
  PrevE=0;
  double Correction=0;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
  SensorVals=ChassisUpdate();
  LGV=SensorVals.HDG-DeltaAngle;
  if(LGV>180) LGV=LGV-360;
  PVal=KVals.kp*LGV;
  IVal=IVal+KVals.ki*LGV*0.02;
  DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;

  SlowMove(CSpeed-Correction,CSpeed+Correction, Speed);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(180,msec);}
  else CStop();
}

void MaxTimePIDTurnOneSide(PIDDataSet KVals,double DeltaAngle,double TE, bool brake){
  double CSpeed=0;
  Zeroing(true,false);
  ChassisDataSet SensorVals;
  SensorVals=ChassisUpdate();
  double PVal=0;
  double IVal=0;
  double DVal=0;
  double LGV=0;
  PrevE=0;
  double Correction=0;
  double LV,RV;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
  SensorVals=ChassisUpdate();
  LGV=SensorVals.HDG-DeltaAngle;
  if(LGV>180) LGV=LGV-360;
  PVal=KVals.kp*LGV;
  IVal=IVal+KVals.ki*LGV*0.02;
  DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;
LV=-CSpeed+Correction;
RV=-CSpeed-Correction;
if(LV>=0)LV=0;
if(RV>=0)RV=0;
  Move(LV,RV);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(200,msec);}
  else CStop();
}


void MoveTimePID(PIDDataSet KVals, int Speed, double TE,double AccT,double ABSHDG, bool brake){
  double CSpeed=0;
  Zeroing(true,false);
  ChassisDataSet SensorVals;
  SensorVals=ChassisUpdate();
  double PVal=0;
  double IVal=0;
  double DVal=0;
  double LGV=0;
  PrevE=0;
  double Correction=0;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
if(fabs(CSpeed)<fabs((double)Speed))
{
  CSpeed+=Speed/AccT*0.02;
}

  SensorVals=ChassisUpdate();
    LGV=SensorVals.HDG-ABSHDG;
  if(LGV>180) LGV=LGV-360;
  PVal=KVals.kp*LGV;
  IVal=IVal+KVals.ki*LGV*0.02;
  DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;

  Move(-CSpeed-Correction,-CSpeed+Correction);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(200,msec);}
  else CStop();
}
