#include "screen_gui.hpp"
#include "vex.h"
#include "movement.hpp"
#include "robot-config.h"


/** prints a rounded rectangle
 * @param x the x position of the rectangle
 * @param y the y position of the rectangle
 * @param width the width of the rectangle
 * @param height the height of the rectangle
 * @param radius how rounded the rectangles are
 * @param color the color of the rounded rectangle
 */
#include "vex.h"

// Draw rounded rectangle outline using proper arc plotting
void drawRoundedRect(int x, int y, int width, int height, int radius, vex::color col) {

  // Clamp radius
  if(radius > width / 2) radius = width / 2;
  if(radius > height / 2) radius = height / 2;

  Brain.Screen.setPenColor(col);

  // --- Straight edges ---
  for(int i = x + radius; i < x + width - radius; i++) {
    Brain.Screen.drawPixel(i, y);                      // Top
    Brain.Screen.drawPixel(i, y + height - 1);         // Bottom
  }

  for(int j = y + radius; j < y + height - radius; j++) {
    Brain.Screen.drawPixel(x, j);                      // Left
    Brain.Screen.drawPixel(x + width - 1, j);          // Right
  }

  // --- Midpoint circle algorithm (only arcs) ---
  int cx1 = x + radius;                      // left center x
  int cx2 = x + width - radius - 1;          // right center x
  int cy1 = y + radius;                      // top center y
  int cy2 = y + height - radius - 1;         // bottom center y

  int dx = radius;
  int dy = 0;
  int err = 1 - dx;

  while(dx >= dy) {

    // Top-left corner
    Brain.Screen.drawPixel(cx1 - dx, cy1 - dy);
    Brain.Screen.drawPixel(cx1 - dy, cy1 - dx);

    // Top-right corner
    Brain.Screen.drawPixel(cx2 + dx, cy1 - dy);
    Brain.Screen.drawPixel(cx2 + dy, cy1 - dx);

    // Bottom-left corner
    Brain.Screen.drawPixel(cx1 - dx, cy2 + dy);
    Brain.Screen.drawPixel(cx1 - dy, cy2 + dx);

    // Bottom-right corner
    Brain.Screen.drawPixel(cx2 + dx, cy2 + dy);
    Brain.Screen.drawPixel(cx2 + dy, cy2 + dx);

    dy++;

    if(err < 0) {
      err += 2 * dy + 1;
    } else {
      dx--;
      err += 2 * (dy - dx) + 1;
    }
  }
}

void DisplayAutoSelector(void)
{

  Brain.Screen.clearScreen();

//auton selector
Brain.Screen.setFont(monoS);
Brain.Screen.setPenWidth(50);
drawRoundedRect(5,5,150,75,25,white);
drawRoundedRect(5,82,150,75,25,white);
drawRoundedRect(5,160,150,75,25,white);
drawRoundedRect(175,5,300,225,30,white);

}

void DisplayWords(void)
{
  Brain.Screen.setPenColor("#ffffff");
  Brain.Screen.setFont(monoL);
  Brain.Screen.printAt(50,50, "Left");
  Brain.Screen.printAt(45,127, "Right");
  Brain.Screen.printAt(50,205, "Both");

}

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
int AutoSelectorVal;

void UpdateDynamic(void)
{
  DisplayAutoSelector();
  DisplayWords();
  Brain.Screen.setFillColor("#84fffd");
  Brain.Screen.setPenColor(black);

if(AutoSelectorVal==1){
  Brain.Screen.drawRectangle(1,25,100,50);
  Brain.Screen.setCursor(3,3);
  Brain.Screen.print("Left 9");

  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor("#84fffd");
  Brain.Screen.setCursor(3,10);
  Brain.Screen.print("LEFT SIDE");
  Brain.Screen.setCursor(4,10);
  Brain.Screen.print("7 WING");
  Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==2){
  Brain.Screen.drawRectangle(375,25,100,50);
  Brain.Screen.setCursor(3,40);
  Brain.Screen.print("Right 9");

  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor("#84fffd");
  Brain.Screen.setCursor(3,10);
  Brain.Screen.print("RIGHT SIDE");
  Brain.Screen.setCursor(4,10);
  Brain.Screen.print("9 BLOCK");
  Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#84fffd");
}

if(AutoSelectorVal==3){
  Brain.Screen.drawRectangle(1,100,100,50);
  Brain.Screen.setCursor(7,3);
  Brain.Screen.print("Left36");

Brain.Screen.setFillColor(black);

    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("LEFT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("34 WING");
Brain.Screen.setFont(monoM);  
  Brain.Screen.setFillColor("#84fffd");
}

if(AutoSelectorVal==4){
Brain.Screen.drawRectangle(375,100,100,50);
  Brain.Screen.setCursor(7,40);
  Brain.Screen.print("RIGHT36");

Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("RIGHT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("9 BLOCK");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==5){
  Brain.Screen.drawRectangle(1,175,100,50);
      Brain.Screen.setCursor(11,3);
  Brain.Screen.print("GOAL CLAMP");

Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("ODOM TEST");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("POSITION UPDATE");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

}

if(AutoSelectorVal==6){
Brain.Screen.drawRectangle(375,175,175,50);
Brain.Screen.setCursor(11,40);
Brain.Screen.print("SAWP");
Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#84fffd");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("BOTH SIDES");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("AWP");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

  }

if(AutoSelectorVal==7){
  Brain.Screen.drawRectangle(187,175,100,50);
  Brain.Screen.setCursor(11,22);
  Brain.Screen.print("Skills");

  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor("#84fffd");
  Brain.Screen.setCursor(3,10);
  Brain.Screen.print("SKILLS");
  Brain.Screen.setCursor(4,10);
  Brain.Screen.print("SKILLS");
  Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#84fffd");

}

}