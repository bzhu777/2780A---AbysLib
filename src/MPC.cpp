#include "vex.h"

#include "math.h"
#include "screen_gui.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
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

const static float trackWidth = 12.5; // in inches
const static int horizon = 3; // how many steps to predict into the future
const static int driveTime = 0.2; // how long each step is in seconds
const static float wheelRadius = wheelDiam/2;

float linearVelocity = 0; // forward velocity
float angularVelocity = 0; // how fast the robot is turning

const float maxLeftVelocity = wheelToMotorRatio*600/60*wheelDiam*M_PI; // max left motor velocity, inches per second (gear ratio * rpm / 60 seconds * wheel circumference)
const float maxRightVelocity = wheelToMotorRatio*600/60*wheelDiam*M_PI; // max right motor velocity, inches per second (gear ratio * rpm / 60 seconds * wheel circumference)

const float maxLinearVelocity = (maxLeftVelocity+maxRightVelocity)/2; // max forward velocity, inches per second
const float maxAngularVelocity = (maxLeftVelocity+maxRightVelocity)/trackWidth; // max turning speed in radians per second


float bestCost = 1e9;
float bestControl[2] = {0, 0}; // {left side velocity, right side velocity}


float changeX=0;
float changeY=0;
float changeHead=0;
float simulatedX=0;
float simulatedY=0;
float simulatedHeading=0;
float totalCost=0;
float cost=0;
int currLeftVelocity=0;
int currRightVelocity=0;

float simCurrLeftVelocity;
float simCurrRightVelocity;

float error = 0;
int firstLeft = 0;
int firstRight = 0;



void MPCmove(double goalX, double goalY)
{
    ofstream MPCdebug("MPCdebug.txt");
    error = sqrt((Xpos-goalX)*(Xpos-goalX) + (Ypos-goalY)*(Ypos-goalY));

    while (error > 1) {
        error = sqrt((Xpos-goalX)*(Xpos-goalX) + (Ypos-goalY)*(Ypos-goalY));

        bestCost = 1e9;
        bestControl[0] = 0;
        bestControl[1] = 0;

        cost = 0;
        bestCost = 1e9;
        simulatedX = Xpos;
        simulatedY = Ypos;
        simulatedHeading = ABSorientation;

        currLeftVelocity = (LM.velocity(pct) + LF.velocity(pct) + LB.velocity(pct)) / 3;
        currRightVelocity = (RM.velocity(pct) + RF.velocity(pct) + RB.velocity(pct)) / 3;

        std::vector<int> leftVelocityPercent = {
            currLeftVelocity-20,
            currLeftVelocity-10,
            currLeftVelocity,
            currLeftVelocity+10,
            currLeftVelocity+20,
        };

        if (abs(currLeftVelocity) <= 15) {
            leftVelocityPercent.push_back(90);
            leftVelocityPercent.push_back(-90);
        }

        for (int &v : leftVelocityPercent) {
            v = std::max(-100, std::min(100, v));
        }



        std::vector<int> RightVelocityPercent = {
            currRightVelocity-20,
            currRightVelocity-10,
            currRightVelocity,
            currRightVelocity+10,
            currRightVelocity+20,
        };

        if (abs(currRightVelocity) <= 15) {
            RightVelocityPercent.push_back(90);
            RightVelocityPercent.push_back(-90);
        }
        

        for (int &v : RightVelocityPercent) {
            v = std::max(-100, std::min(100, v));
        } 

    

    
        for (int simulationNumber = 0; simulationNumber < leftVelocityPercent.size(); simulationNumber++) {
            simCurrLeftVelocity=leftVelocityPercent[simulationNumber]*wheelToMotorRatio*6/60*wheelDiam*M_PI;

            for (int simulationNumber2 = 0; simulationNumber2 < RightVelocityPercent.size(); simulationNumber2++) {
                simCurrRightVelocity=RightVelocityPercent[simulationNumber2]*wheelToMotorRatio*6/60*wheelDiam*M_PI;

                cost = 0;
                simulatedX = Xpos;
                simulatedY = Ypos;
                simulatedHeading = ABSorientation;
            

                    // Kinematics based on -- https://msl.cs.uiuc.edu/planning/node659.html
                    changeX=0.5*(simCurrLeftVelocity+simCurrRightVelocity) * cos(simulatedHeading);
                    changeY=0.5*(simCurrLeftVelocity+simCurrRightVelocity) * sin(simulatedHeading);
                    changeHead=wheelRadius/trackWidth*(simCurrRightVelocity-simCurrLeftVelocity);
                
                    simulatedY+=changeY*0.1;
                    simulatedX+=changeX*0.1;
                    simulatedHeading+=changeHead*0.1;

                    cost += ((simulatedX - goalX) * (simulatedX - goalX)) + ((simulatedY - goalY) * (simulatedY - goalY));
                    cost += 0.001 * ((simCurrRightVelocity * simCurrRightVelocity) + (simCurrLeftVelocity * simCurrLeftVelocity)); 
        
                    for (int i =0; i < horizon-1; i++) {

                    if (cost > bestCost) {
                        break;
                    }

                    firstLeft = leftVelocityPercent[simulationNumber];
                    firstRight = RightVelocityPercent[simulationNumber2];

                    currLeftVelocity = leftVelocityPercent[simulationNumber];
                    currRightVelocity = RightVelocityPercent[simulationNumber2];


                std::vector<int> leftVelocityPercent = {
                currLeftVelocity-10,
                currLeftVelocity,
                currLeftVelocity+10,
                
                };

                if (abs(currLeftVelocity) <= 15) {
                    leftVelocityPercent.push_back(90);
                    leftVelocityPercent.push_back(-90);
                }

                for (int &v : leftVelocityPercent) {
                    v = std::max(-100, std::min(100, v));
                }



                std::vector<int> RightVelocityPercent = {
                    currRightVelocity-10,
                    currRightVelocity,
                    currRightVelocity+10,
                };

                if (abs(currRightVelocity) <= 15) {
                    RightVelocityPercent.push_back(90);
                    RightVelocityPercent.push_back(-90);
                }

                for (int &v : RightVelocityPercent) {
                    v = std::max(-100, std::min(100, v));
                } 

                for (int simulationNumber = 0; simulationNumber < leftVelocityPercent.size(); simulationNumber++) {
                    simCurrLeftVelocity=leftVelocityPercent[simulationNumber]*wheelToMotorRatio*6/60*wheelDiam*M_PI; //converts percent to inch per sec

                    for (int simulationNumber2 = 0; simulationNumber2 < RightVelocityPercent.size(); simulationNumber2++) {
                        simCurrRightVelocity=RightVelocityPercent[simulationNumber2]*wheelToMotorRatio*6/60*wheelDiam*M_PI;

                        // Kinematics based on -- https://msl.cs.uiuc.edu/planning/node659.html
                        changeX=0.5*(simCurrLeftVelocity+simCurrRightVelocity) * cos(simulatedHeading);
                        changeY=0.5*(simCurrLeftVelocity+simCurrRightVelocity) * sin(simulatedHeading);
                        changeHead=wheelRadius/trackWidth*(simCurrRightVelocity-simCurrLeftVelocity);
            
                        simulatedY+=changeY*0.1;
                        simulatedX+=changeX*0.1;
                        simulatedHeading+=changeHead*0.1;

                        cost += ((simulatedX - goalX) * (simulatedX - goalX)) + ((simulatedY - goalY) * (simulatedY - goalY));
                        cost += 0.001 * ((simCurrRightVelocity * simCurrRightVelocity) + (simCurrLeftVelocity * simCurrLeftVelocity));

                        MPCdebug << firstLeft << " " << firstRight << " " << cost << endl;
                        if (cost < bestCost) {
                            bestCost = cost;
                            bestControl[0] = firstLeft;
                            bestControl[1] = firstRight;
                        }
                        }
                    }
                }
            }
        }

    }

    Move(bestControl[0], bestControl[1]);
    wait(100,msec);

    MPCdebug << "Best Control: " << bestControl[0] << " " << bestControl[1] << " " << "Best Cost: " << bestCost << endl;
    MPCdebug.close();
}