#include "vex.h"
#include "math.h"
#include "movement.hpp"
#include "pid.hpp"

using namespace vex;

PIDDataSet TestPara;
int PrevE;

double ComputePID(PIDDataSet KVals, double error, double &integral, double &prevError, double deltaTime)
{
}

void MoveEncoderPID(PIDDataSet KVals, int Speed, double dist, double AccT, double ABSHDG, bool brake)
{
}

void TurnMaxTimePID(PIDDataSet KVals, double DeltaAngle, double TE, bool brake)
{
}

void MoveTimePID(PIDDataSet KVals, int Speed, double TE, double AccT, double ABSHDG, bool brake)
{
}
