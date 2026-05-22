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

const static float trackWidth = 13.5; // in inches
const static int horizon = 10; // how many steps to predict into the future

float linearVelocity = 0; // forward velocity
float angularVelocity = 0; // how fast the robot is turning

const float maxLeftVelocity = wheelToMotorRatio*600/60*wheelDiam*M_PI; // max left motor velocity, inches per second
const float maxRightVelocity = wheelToMotorRatio*600/60*wheelDiam*M_PI; // max right motor velocity, inches per second

const float maxLinearVelocity = (maxLeftVelocity+maxRightVelocity)/2; // max forward velocity, inches per second
const float maxAngularVelocity = (maxLeftVelocity+maxRightVelocity)/trackWidth; // max turning speed in radians per second


float bestCost = 1e9;
float bestControl[2] = {0, 0}; // {linear velocity, angular velocity}

float simulatedX=0;
float simulatedY=0;
float simulatedHeading=0;
float totalCost=0;


void predictFutureState(double goalX, double goalY)
{
    simulatedX = Xpos;
    simulatedY = Ypos;
    simulatedHeading = ABSorientation;

    for (int i = 0; i < horizon; i++) {
        // Simple kinematic model
        
    }
}