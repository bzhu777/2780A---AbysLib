#ifndef MOVEMENT_H
#define MOVEMENT_H

extern int turninverse;
extern int JB;
extern int PB;
extern int PX;
extern int JX;

//ODOM VARIABLES

extern float TrackingFront;
extern float prevTrackingFrontLeft;
extern float prevTrackingFrontRight;
extern float TrackingSide;
extern float prevTrackingSide;
extern float Xpos;
extern float Ypos;
extern float ThetaDeg;
extern float prevHDGpos;
extern float ABSorientation;

extern const float  invTrackWidth;
extern const float  OffsetAVG;

struct OdomDataSet{
  float CurrTrackingFrontLeft;
  float CurrTrackingFrontRight;
  float CurrTrackingSide;
};

struct OdomDeltaSet{
  float DeltaTrackingFrontLeft;
  float DeltaTrackingFrontRight;
  float DeltaTrackingSide;
};

struct ChassisDataSet{
  int Left;
  int Right;
  float Avg;   // Average between left and right of the drive train
  int Diff;     // Left - Right
  float HDG;   // Robot heading
};

struct PIDDataSet{
  double kp;
  double ki;
  double kd;
};

//ODOM FUNCTIONS

extern void OdomZeroing(void);
extern void UpdatePos(void);
extern void SetPos(float X, float Y, float HDG);
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
extern void SpinLift(int val);
extern void RunChainbar(int val);
extern int PrevE;
extern void MoveEncoderPID(PIDDataSet KVals, int Speed, double dist,double AccT, double ABSHDG,bool brake);
extern void TurnMaxTimePID(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
extern void TurnToAngle(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
extern void TurnToPoint(PIDDataSet KVals,double Xval, double Yval,double TE, bool brake);
extern void predictFutureState(double goalX, double goalY);
extern void MPCmove(double goalX, double goalY, bool brake);
void MaxTimePIDTurnOneSide(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
void MoveTimePID(PIDDataSet KVals, int Speed, double TE,double AccT,double ABSHDG, bool brake);


#endif
