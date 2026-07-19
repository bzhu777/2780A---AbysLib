using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LF;
extern motor LM;
extern motor RF;
extern motor RM;
extern motor LB;
extern motor RB;
extern motor Intake1;
extern motor ChainBar;
extern motor Lift;
extern digital_out Redirect1;
extern inertial Gyro;
extern rotation xROdom;
extern rotation xLOdom;
extern rotation yOdom;
extern rotation chainbar;
extern aivision Resetter;

extern const float wheelDiam;
extern const float wheelToMotorRatio;

extern const float OdomDiam;
extern const float LeftOdomFrontOffset;
extern const float RightOdomFrontOffset;
extern const float OdomSideOffset;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );