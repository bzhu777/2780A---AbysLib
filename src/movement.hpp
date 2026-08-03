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

//ODOM FUNCTIONS

extern void OdomZeroing(void);
extern void UpdatePos(void);
extern void SetPos(float X, float Y, float HDG);
extern OdomDeltaSet OdomGetDistTravelled();
extern OdomDataSet OdomUpdate();

//PID FUNCTIONS

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
extern void predictFutureState(double goalX, double goalY);
extern void MPCmove(double goalX, double goalY, bool brake);


#endif
