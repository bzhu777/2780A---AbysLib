#include "vex.h"
#include <math.h>

#include <iostream>
/** Gets the distance travelled in a linear path by the robot
 * 
 * @param degreesTravelled the degrees travelled
 * @return the distance travelled by the motors, in inches
 */
double get_dist_travelled(double degreesTravelled) {
    std::cout << "gear ratio " << wheelToMotorRatio << M_PI*wheelDiam << std::endl;
    std::cout << degreesTravelled * wheelToMotorRatio / 360 * (M_PI*wheelDiam) << std::endl;
    return fabs(degreesTravelled * wheelToMotorRatio / 360 * (M_PI*wheelDiam));
}

double get_Odom_dist_travelled(double degreesTravelled) {
    std::cout << "gear ratio " << odomWheelToMotorRatio << M_PI*odomWheelDiam << std::endl;
    std::cout << degreesTravelled * odomWheelToMotorRatio / 360 * (M_PI*odomWheelDiam) << std::endl;
    return fabs(degreesTravelled * odomWheelToMotorRatio / 360 * (M_PI*odomWheelDiam));
}