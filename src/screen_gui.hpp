#ifndef SCREEN_GUI_H
#define SCREEN_GUI_H
#include "vex.h"

extern int AutoSelectorVal;
extern int SideVal;

extern void DisplayAutoSelector();
extern void DisplayWords();
extern void UpdateDynamic();
extern void drawRoundedRect(int x, int y, int width, int height, int radius, vex::color col);

#endif
