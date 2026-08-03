#ifndef PID_H
#define PID_H

struct PIDDataSet{
  double kp;
  double ki;
  double kd;
};

extern PIDDataSet TestPara;
extern int PrevE;

double ComputePID(PIDDataSet KVals, double error, double &integral, double &prevError, double deltaTime);
void MoveEncoderPID(PIDDataSet KVals, int Speed, double dist, double AccT, double ABSHDG, bool brake);
void TurnMaxTimePID(PIDDataSet KVals, double DeltaAngle, double TE, bool brake);
void TurnToAngle(PIDDataSet KVals, double DeltaAngle, double TE, bool brake);
void TurnToPoint(PIDDataSet KVals, float Xval, float Yval, float TE, bool brake);
void MaxTimePIDTurnOneSide(PIDDataSet KVals, double DeltaAngle, double TE, bool brake);
void MoveTimePID(PIDDataSet KVals, int Speed, double TE, double AccT, double ABSHDG, bool brake);

#endif
