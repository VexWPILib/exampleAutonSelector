// Copyright (c) VexWPIApi contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the VexWPIApi BSD license file in the root directory of this project.

#pragma once

#include "v5lvgl.h"
#include "lv_conf.h"

#define AUTON_SELECTOR_DEFAULT 1
#define AUTON_SELECTOR_AUTONS "0", "1", "2", "3", "4", "SKILLS"

#define AUTON_SELECTOR_RED_SIDE   1
#define AUTON_SELECTOR_BLUE_SIDE -1

#define AUTON_SELECTOR_LEFT_SIDE   1
#define AUTON_SELECTOR_RIGHT_SIDE -1

#define AUTON_SELECTOR_TANK_DRIVE   1
#define AUTON_SELECTOR_ARCADE_DRIVE 0

#define AUTON_SELECTOR_DRIVE_DEFAULT AUTON_SELECTOR_ARCADE_DRIVE
#define AUTON_SELECTOR_SIDE_DEFAULT AUTON_SELECTOR_LEFT_SIDE
#define AUTON_SELECTOR_COLOR_DEFAULT AUTON_SELECTOR_RED_SIDE

#pragma once

namespace vpi {
  namespace ui {
    extern int autonSelection;
    extern int redOrBlue;
    extern int leftOrRight;
    extern int arcadeOrTank;

    extern const char *btnmMap[];
    extern const char *btnmMapLeftRight[];
    extern const char *btnmMapArcadeTank[];
    extern const char *btnmMapRedBlue[];

    void selectorInit();
  } // ui
} // vpi
