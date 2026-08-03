#ifndef LIFT_DISPLAY_H
#define LIFT_DISPLAY_H

extern int LiftDisplayCounter;
extern int ChainbarDisplayCounter;

extern void ResetLiftDisplayCounter();
extern void UpdateLiftDisplayCounter();
extern void DrawLiftDisplayCounter();
extern void ResetChainbarDisplayCounter();
extern void UpdateChainbarDisplayCounter();
extern void DrawChainbarDisplayCounter();
extern int LiftDisplayTask();

#endif
