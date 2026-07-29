#include "vex.h"
#include "lift_display.hpp"
#include "robot-config.h"

#include <math.h>

int LiftDisplayCounter = 0;
double lastLiftPosition = 0.0;

void ResetLiftDisplayCounter() {
  lastLiftPosition = Lift.position(degrees);
  LiftDisplayCounter = 0;
}

void UpdateLiftDisplayCounter() {
  double currentPosition = Lift.position(degrees);
  double delta = currentPosition - lastLiftPosition;
  int deltaSteps = static_cast<int>(round(delta));

  if (deltaSteps != 0) {
    LiftDisplayCounter += deltaSteps;
    lastLiftPosition = currentPosition;
  }
}

void DrawLiftDisplayCounter() {
  Brain.Screen.setFont(monoM);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Lift Count:            ");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Lift Count: ");
  Brain.Screen.print(LiftDisplayCounter);
  Brain.Screen.print(" deg");
}

int LiftDisplayTask() {
  ResetLiftDisplayCounter();

  while (true) {
    UpdateLiftDisplayCounter();
    DrawLiftDisplayCounter();
    wait(20, msec);
  }

  return 0;
}
