#ifndef MOVEMENT_H
#define MOVEMENT_H

extern int turninverse;
extern int JB;
extern int PB;
extern int PX;
extern int JX;

//ODOM VARIABLES

extern double TrackingFront;
extern double prevTrackingFrontLeft;
extern double prevTrackingFrontRight;
extern double TrackingSide;
extern double prevTrackingSide;
extern double Xpos;
extern double Ypos;
extern double ThetaDeg;
extern double prevHDGpos;
extern double ABSorientation;


struct OdomDataSet{
  double CurrTrackingFrontLeft;
  double CurrTrackingFrontRight;
  double CurrTrackingSide;
};

struct OdomDeltaSet{
  double DeltaTrackingFrontLeft;
  double DeltaTrackingFrontRight;
  double DeltaTrackingSide;
};

struct ChassisDataSet{
  int Left;
  int Right;
  double Avg;   // Average between left and right of the drive train
  int Diff;     // Left - Right
  double HDG;   // Robot heading
};

struct PIDDataSet{
  double kp;
  double ki;
  double kd;
};

//ODOM FUNCTIONS

extern void OdomZeroing(void);
extern void UpdatePos(void);
extern void SetPos(double X, double Y, double HDG);
extern OdomDeltaSet OdomGetDistTravelled();
extern OdomDataSet OdomUpdate();

//PID FUNCTIONS

extern PIDDataSet TestPara;
extern void Zeroing(bool dist, bool HDG);
extern ChassisDataSet ChassisUpdate();
extern OdomDataSet OdomUpdate();
extern void Move(int left, int right);
extern void SlowMove(int left, int right, int speed);
extern void BStop();
extern void CStop();
extern void RunRoller(int val);
extern void MiddleScore();
extern void HighScore();
extern void NeutralScore();
extern int PrevE;
extern void MoveEncoderPID(PIDDataSet KVals, int Speed, double dist,double AccT, double ABSHDG,bool brake);
extern void TurnMaxTimePID(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
extern void TurnToAngle(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
extern void TurnToPoint(PIDDataSet KVals,double Xval, double Yval,double TE, bool brake);
extern void predictFutureState(double goalX, double goalY);
void MaxTimePIDTurnOneSide(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
void MoveTimePID(PIDDataSet KVals, int Speed, double TE,double AccT,double ABSHDG, bool brake);


#endif
