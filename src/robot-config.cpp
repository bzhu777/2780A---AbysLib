#include "vex.h"
#include "robot-config.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LF = motor(PORT1, ratio6_1, false);
motor LM = motor(PORT1, ratio18_1, false);
motor LB = motor(PORT1, ratio6_1, false);
motor RF = motor(PORT1, ratio6_1, true);
motor RM = motor(PORT1, ratio18_1, true);
motor RB = motor(PORT1, ratio6_1, true);
motor Intake1 = motor(PORT10, ratio6_1, true);
motor Intake2 = motor(PORT21, ratio6_1, true);
motor ChainBar = motor(PORT1, ratio18_1, false);

motor Lift = motor(PORT1, ratio36_1, false);

digital_out Claw = digital_out(Brain.ThreeWirePort.A);
inertial Gyro = inertial(PORT1, turnType::right);
rotation chainbar = rotation(PORT1);
rotation xOdom = rotation(PORT1);
rotation yOdom = rotation(PORT1);
aivision Resetter = aivision(PORT1, aivision::ALL_TAGS);

//Naming convention: 
// Important variables
const float wheelDiam = 2.75;
const float OdomDiam = 2; //odometry wheel diameter in inches
const float LeftOdomFrontOffset = 5.0; // tracking center distance to wheel
const float RightOdomFrontOffset = 5.0; // tracking center distance to wheel
const float OdomSideOffset = 5.0; //distance from center of robot to side odometry wheel

const float wheelToMotorRatio = 36.0/48;

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}