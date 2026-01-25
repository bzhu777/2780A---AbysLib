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
extern motor Intake2;
extern digital_out Wing;
extern digital_out Redirect1;
extern digital_out Redirect2;
extern digital_out Scraper;
extern inertial Gyro;
extern rotation xOdom;
extern rotation yOdom;

extern const double wheelDiam;
extern const double OdomDiam;

extern const double wheelToMotorRatio;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );