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
drawRoundedRect(175,5,303,230,30,white);
Brain.Screen.setPenWidth(6);
Brain.Screen.drawLine(165,0,165,250);

}

void DisplayWords(void)
{
  Brain.Screen.setPenColor("#ffffff");
  Brain.Screen.setFont(monoL);
  Brain.Screen.printAt(50,50, "Left");
  Brain.Screen.printAt(45,127, "Right");
  Brain.Screen.printAt(50,205, "Both");

}


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
int SideVal;

void UpdateDynamic(void)
{
  DisplayAutoSelector();
  DisplayWords();
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(white);

if(SideVal==1){ // left
  drawRoundedRect(5,5,150,75,25,ClrLightBlue);
  Brain.Screen.setPenColor("#58a7fc");
  Brain.Screen.printAt(50,50, "Left");

  drawRoundedRect(183,15,140,60,20,white); // auto 1
  drawRoundedRect(330,15,140,60,20,white); // auto 2
  drawRoundedRect(183,87,140,60,20,white); // auto 3
  drawRoundedRect(330,87,140,60,20,white); // auto 4
  drawRoundedRect(183,164,285,60,20,white); // confirm

  Brain.Screen.setPenColor("#ffffff");
  Brain.Screen.setFont(monoM); 

  Brain.Screen.printAt(200,50, "Auto 1");
  Brain.Screen.printAt(200,122, "Auto 3");
  Brain.Screen.printAt(347,50, "Auto 2");
  Brain.Screen.printAt(347,122, "Auto 4");
  Brain.Screen.printAt(280,200, "Confirm");
}

if(SideVal==2){ // right
  drawRoundedRect(5,82,150,75,25,ClrLightBlue);
  Brain.Screen.setPenColor("#58a7fc");
  Brain.Screen.printAt(45,127, "Right");

  drawRoundedRect(183,15,140,60,20,white); // auto 5
  drawRoundedRect(183,87,140,60,20,white); // auto 7

  drawRoundedRect(330,15,140,60,20,white); // auto 6
  drawRoundedRect(330,87,140,60,20,white); // auto 8
  drawRoundedRect(183,164,285,60,20,white); // confirm

  Brain.Screen.setPenColor("#ffffff");
  Brain.Screen.setFont(monoM);

  Brain.Screen.printAt(200,50, "Auto 5");
  Brain.Screen.printAt(200,122, "Auto 7");
  Brain.Screen.printAt(347,50, "Auto 6");
  Brain.Screen.printAt(347,122, "Auto 8");
  Brain.Screen.printAt(280,200, "Confirm");



}

if(SideVal==3){ // both
  drawRoundedRect(5,160,150,75,25,ClrLightBlue);
  Brain.Screen.setPenColor("#58a7fc");
  Brain.Screen.printAt(50,205, "Both");

  drawRoundedRect(185,15,135,140,20,white); // auto 9
  drawRoundedRect(330,15,135,140,20,white); // auto 10

  drawRoundedRect(183,164,285,60,20,white);

  Brain.Screen.setPenColor("#ffffff");
  Brain.Screen.setFont(monoM);

  Brain.Screen.printAt(200,87, "Auto 9");
  Brain.Screen.printAt(347,87, "Auto 10");
  Brain.Screen.printAt(280,200, "Confirm");
}



if(AutoSelectorVal==1){
  drawRoundedRect(183,15,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==2){
  drawRoundedRect(330,15,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==3){
  drawRoundedRect(183,87,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==4){
  drawRoundedRect(330,87,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==5){
  drawRoundedRect(183,15,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==6){
  drawRoundedRect(330,15,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==7){
  drawRoundedRect(183,87,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==8){
  drawRoundedRect(330,87,140,60,20,ClrLightBlue);
}

if(AutoSelectorVal==9){
  drawRoundedRect(185,15,135,140,20,ClrLightBlue);
}

if(AutoSelectorVal==10){
  drawRoundedRect(330,15,135,140,20,ClrLightBlue);
}
}