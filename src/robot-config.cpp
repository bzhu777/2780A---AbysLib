#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LF = motor(PORT20, ratio6_1, false);
motor LM = motor(PORT2, ratio6_1, false);
motor LB = motor(PORT1, ratio6_1, false);
motor RF = motor(PORT11, ratio6_1, true);
motor RM = motor(PORT12, ratio6_1, true);
motor RB = motor(PORT13, ratio6_1, true);
motor Intake1 = motor(PORT10, ratio6_1, true);
motor Intake2 = motor(PORT9, ratio6_1, false);

digital_out Wing = digital_out(Brain.ThreeWirePort.A);
digital_out Scraper = digital_out(Brain.ThreeWirePort.D);
digital_out Redirect1 = digital_out(Brain.ThreeWirePort.B);
digital_out Redirect2 = digital_out(Brain.ThreeWirePort.C);
inertial Gyro = inertial(PORT5);
encoder x_odom = encoder(Brain.ThreeWirePort.E);
encoder y_odom = encoder(Brain.ThreeWirePort.F);
//Naming convention: 
// Important variables
const double wheelDiam = 2.75;
const double odomWheelDiam = 2.75;
const double odomWheelToMotorRatio = 1.0;
const double wheelToMotorRatio = 36.0/48;

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