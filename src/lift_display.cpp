#include "vex.h"
#include "lift_display.hpp"
#include "robot-config.h"

#include <math.h>

int LiftDisplayCounter = 0;
int ChainbarDisplayCounter = 0;

void ResetLiftDisplayCounter() {
  LiftDisplayCounter = static_cast<int>(round(Lift.position(degrees)));
}

void UpdateLiftDisplayCounter() {
  LiftDisplayCounter = static_cast<int>(round(Lift.position(degrees)));
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

void ResetChainbarDisplayCounter() {
  ChainbarDisplayCounter = static_cast<int>(round(ChainBar.position(degrees)));
}

void UpdateChainbarDisplayCounter() {
  ChainbarDisplayCounter = static_cast<int>(round(ChainBar.position(degrees)));
}

void DrawChainbarDisplayCounter() {
  Brain.Screen.setFont(monoM);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Chainbar Count:            ");
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Chainbar Count: ");
  Brain.Screen.print(ChainbarDisplayCounter);
  Brain.Screen.print(" deg");
}

int LiftDisplayTask() {
  ResetLiftDisplayCounter();
  ResetChainbarDisplayCounter();

  while (true) {
    UpdateLiftDisplayCounter();
    UpdateChainbarDisplayCounter();
    DrawLiftDisplayCounter();
    DrawChainbarDisplayCounter();
    wait(20, msec);
  }

  return 0;
}
