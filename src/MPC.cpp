#include "vex.h"

#include "math.h"
#include "screen_gui.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

#include <iostream>

using namespace vex;

// Breakdown of Model Predictive Control (MPC)
// 1. Predict future robot state
// 2. Simulate different robot paths
// 3. Pick the best one based on cost
// 4. apply the first step
// 5. repeat back to 1

// This MPC will use the following...
// X position
// Y position
// Heading
// Forward velocity
// Angular velocity

void predictFutureState(double goalX, double goalY)
{

}