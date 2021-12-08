// Copyright (C) 2019 by James Pearman
//
// Permission is hereby granted, free of charge, to any person obtaining 
// a copy of this software and associated documentation files (the 
// "Software"), to deal in the Software without restriction, including 
// without l> imitation the rights to use, copy, modify, merge, publish, 
// distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so, subject 
// to the following conditions:
//
// The above copyright notice and this permission notice shall be included 
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:                                                                 */
/*    Created:      Thu Nov 18 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vpi/vpi.h"
#include "Button.h"

using namespace vex;
using namespace vpi;

// A global instance of competition
competition Competition;

#define AUTON_BUTTONS_X_START 20
#define AUTON_BUTTONS_Y_START 20
#define AUTON_BUTTONS_WIDTH 60
#define AUTON_BUTTONS_HEIGHT 50

button buttonsAuton[] = {
  {AUTON_BUTTONS_X_START + 0 * (AUTON_BUTTONS_WIDTH + 10), AUTON_BUTTONS_Y_START + 0 * (AUTON_BUTTONS_HEIGHT + 10), 
    AUTON_BUTTONS_WIDTH, AUTON_BUTTONS_HEIGHT, "A1", "A1", false, vex::color::blue, vex::color::cyan},
  {AUTON_BUTTONS_X_START + 1 * (AUTON_BUTTONS_WIDTH + 10), AUTON_BUTTONS_Y_START + 0 * (AUTON_BUTTONS_HEIGHT + 10), 
    AUTON_BUTTONS_WIDTH, AUTON_BUTTONS_HEIGHT, "A2", "A2", false, vex::color::blue, vex::color::cyan},
  {AUTON_BUTTONS_X_START + 2 * (AUTON_BUTTONS_WIDTH + 10), AUTON_BUTTONS_Y_START + 0 * (AUTON_BUTTONS_HEIGHT + 10), 
    AUTON_BUTTONS_WIDTH, AUTON_BUTTONS_HEIGHT, "A3", "A3", false, vex::color::blue, vex::color::cyan},
  {AUTON_BUTTONS_X_START + 3 * (AUTON_BUTTONS_WIDTH + 10), AUTON_BUTTONS_Y_START + 0 * (AUTON_BUTTONS_HEIGHT + 10), 
    AUTON_BUTTONS_WIDTH, AUTON_BUTTONS_HEIGHT, "A4", "A4", false, vex::color::blue, vex::color::cyan}
};

button buttonsColor[] = {
  {AUTON_BUTTONS_X_START + 0 * (AUTON_BUTTONS_WIDTH + 10), AUTON_BUTTONS_Y_START + 1 * (AUTON_BUTTONS_HEIGHT + 10), 
    AUTON_BUTTONS_WIDTH, AUTON_BUTTONS_HEIGHT, "RED", "BLUE", false, vex::color::red, vex::color::blue}
};

button buttonsDrive[] = {
  {AUTON_BUTTONS_X_START + 0 * (AUTON_BUTTONS_WIDTH + 10), AUTON_BUTTONS_Y_START + 2 * (AUTON_BUTTONS_HEIGHT + 10), 
    AUTON_BUTTONS_WIDTH, AUTON_BUTTONS_HEIGHT, "ARCADE", "TANK", false, vex::color::blue, vex::color::cyan}
};

int g_autonSelection = AUTON_SELECTOR_DEFAULT;
int g_redOrBlue = AUTON_SELECTOR_COLOR_DEFAULT;
int g_leftOrRight = AUTON_SELECTOR_SIDE_DEFAULT;
int g_arcadeOrTank = AUTON_SELECTOR_DRIVE_DEFAULT;

int findButton( button *buttons, int nButtons,  int16_t xpos, int16_t ypos ) {
  for( int index=0;index < nButtons;index++) {
    button *pButton = &buttons[ index ];
    if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
      continue;

    if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
      continue;
    
    return(index);
  }
  return (-1);
}

void setSelected( button *buttons, int nButtons,  int16_t selectedIndex ) {
  for( int index=0;index < nButtons;index++) {
    button *pButton = &buttons[ index ];
    pButton->state = (index == selectedIndex ? true : false);
  }
}

void userTouchCallbackReleased() {
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  int nAutonButtons = sizeof(buttonsAuton) / sizeof(button);
  int nColorButtons = sizeof(buttonsColor) / sizeof(button);
  int nDriveButtons = sizeof(buttonsDrive) / sizeof(button);
  //printf("Touch Released\n");

  if( (index = findButton(buttonsAuton, nAutonButtons, xpos, ypos )) >= 0 ) {
    g_autonSelection = index;
    setSelected(buttonsAuton, nAutonButtons, index);
    drawButtons(buttonsAuton, nAutonButtons);
    printf("AUTON CHANGED to %d\n",g_autonSelection);
  } else if( (index = findButton(buttonsColor, nColorButtons, xpos, ypos )) >= 0 ) {
    buttonsColor[index].state = !buttonsColor[index].state;
    if(buttonsColor[index].state) {
      g_redOrBlue = AUTON_SELECTOR_BLUE_SIDE;
    } else {
      g_redOrBlue = AUTON_SELECTOR_RED_SIDE;
    }
    drawButtons(buttonsColor, nColorButtons);
    printf("COLOR CHANGED to %d\n",g_redOrBlue);
  } else if( (index = findButton(buttonsDrive, nDriveButtons, xpos, ypos )) >= 0 ) {
    buttonsDrive[index].state = !buttonsDrive[index].state;
    if(buttonsDrive[index].state) {
      g_arcadeOrTank = AUTON_SELECTOR_TANK_DRIVE;
    } else {
      g_arcadeOrTank = AUTON_SELECTOR_ARCADE_DRIVE;
    }
    drawButtons(buttonsDrive, nDriveButtons);
    printf("DRIVE CHANGED to %d\n",g_arcadeOrTank);
  }
}

void drawButtons(button *buttons, int nButtons) {
  for( int index=0;index < nButtons;index++) {
    button *b = &buttons[ index ];
    vex::color c = vex::color::blue;
    c = b->colorUnselected;
    const char *text = b->label;
    if (b->state) {
      c = b->colorSelected;
      text = b->labelSelected;
    }

    Brain.Screen.setFillColor(c);
    Brain.Screen.drawRectangle(b->xpos, b->ypos, b->width, b->height);
    int x = b->xpos + b->width / 2 - Brain.Screen.getStringWidth(text) / 2;
    int y = b->ypos + b->height / 2 + Brain.Screen.getStringHeight(text) / 2;
    Brain.Screen.printAt(x, y, false, text);
  }
}

void initButtons() {
  int nAutonButtons = sizeof(buttonsAuton) / sizeof(button);
  int nColorButtons = sizeof(buttonsColor) / sizeof(button);
  int nDriveButtons = sizeof(buttonsDrive) / sizeof(button);
  setSelected(buttonsAuton, nAutonButtons, g_autonSelection);
  drawButtons(buttonsAuton, nAutonButtons);
  drawButtons(buttonsColor, nColorButtons);
  drawButtons(buttonsDrive, nDriveButtons);
  Brain.Screen.released( userTouchCallbackReleased );
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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  int a = g_autonSelection;
  if(a == 0) {
    // Do Auton Routine 0
    printf("Do autonSelection ==  0\n");
  } else if (a == 1) {
    // Do Auton Routine 1
    printf("Do autonSelection ==  1\n");
  } else if (a == 2) {
    // Do Auton Routine 2
    printf("Do autonSelection ==  2\n");
  } else if (a == 3) {
    // Do Auton Routine 3
    printf("Do autonSelection ==  3\n");
  } else if (a == 4) {
    // Do Auton Routine 4
    printf("Do autonSelection ==  4\n");
  } else if (a == 5) {
    // Do Programming Skills Routine
    printf("Do Programming Skills\n");
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Competition.bStopAllTasksBetweenModes = false;

  // Run the pre-autonomous function.
  pre_auton();

  // Display the Auton Selector on the Brain
  initButtons();

  // Prevent main from exiting with an infinite loop.
  bool wasEnabled = false;
  while (true) {
    bool curState = Competition.isEnabled();
    if(wasEnabled && !curState) {
      printf("DISABLED!\n");
    } else if(!wasEnabled && curState) {
      printf("ENABLED!\n");
    }
    wasEnabled = Competition.isEnabled();
    wait(1000, msec);
  }
}
