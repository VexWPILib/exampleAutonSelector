// Copyright (c) VexWPIApi contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the VexWPIApi BSD license file in the root directory of this project.

#include "AutonSelector.h"

namespace vpi {

  namespace ui {
    int autonSelection = AUTON_SELECTOR_DEFAULT;
    int redOrBlue = AUTON_SELECTOR_COLOR_DEFAULT;
    int leftOrRight = AUTON_SELECTOR_SIDE_DEFAULT;
    int arcadeOrTank = AUTON_SELECTOR_DRIVE_DEFAULT;

    const char *btnmMap[] = {AUTON_SELECTOR_AUTONS,""};
    const char *btnmMapLeftRight[] = {"LEFT", "RIGHT", ""};
    const char *btnmMapArcadeTank[] = {"ARCADE", "TANK", ""};
    const char *btnmMapRedBlue[] = {"RED", "BLUE", ""};

    lv_obj_t *autonBtnm;
    lv_obj_t *colorBtnm;
    lv_obj_t *sideBtnm;
    lv_obj_t *driveBtnm;
    
    void btnmAutonEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        //const char * txt = lv_btnmatrix_get_active_btn_text(obj);
        autonSelection = lv_btnmatrix_get_active_btn(obj);
        lv_btnmatrix_set_focused_btn(obj, autonSelection);
        lv_btnmatrix_set_btn_ctrl(obj, autonSelection, LV_BTNMATRIX_CTRL_CHECK_STATE);
      }
    }

    void btnmColorEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        //const char * txt = lv_btnmatrix_get_active_btn_text(obj);
        int i = lv_btnmatrix_get_active_btn(obj);
        if(i == 0) {
          redOrBlue = AUTON_SELECTOR_RED_SIDE;
        } else {
          redOrBlue = AUTON_SELECTOR_BLUE_SIDE;
        }
        lv_btnmatrix_set_focused_btn(obj, i);
        lv_btnmatrix_set_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_CHECK_STATE);
        static lv_style_t style1;
        if(redOrBlue == AUTON_SELECTOR_RED_SIDE) {
          lv_style_set_bg_color(&style1, LV_STATE_CHECKED | LV_STATE_FOCUSED | LV_STATE_DEFAULT, LV_COLOR_RED);
        } else {
          lv_style_set_bg_color(&style1, LV_STATE_CHECKED | LV_STATE_FOCUSED | LV_STATE_DEFAULT, LV_COLOR_BLUE);
        }
        lv_obj_add_style(obj,LV_BTNMATRIX_PART_BTN, &style1);
      }
    }

    void btnmSideEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        //const char * txt = lv_btnmatrix_get_active_btn_text(obj);
        int i = lv_btnmatrix_get_active_btn(obj);
        if(i == 0) {
          leftOrRight = AUTON_SELECTOR_LEFT_SIDE;
        } else {
          leftOrRight = AUTON_SELECTOR_RIGHT_SIDE;
        }
        lv_btnmatrix_set_focused_btn(obj, i);
        lv_btnmatrix_set_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_CHECK_STATE);
      }
    }

    void btnmDriveEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        //const char * txt = lv_btnmatrix_get_active_btn_text(obj);
        int i = lv_btnmatrix_get_active_btn(obj);
        if(i == 0) {
          arcadeOrTank = AUTON_SELECTOR_ARCADE_DRIVE;
        } else {
          arcadeOrTank = AUTON_SELECTOR_TANK_DRIVE;
        }
        lv_btnmatrix_set_focused_btn(obj, i);
        lv_btnmatrix_set_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_CHECK_STATE);
      }
    }

    void selectorInit(){
      // Set the full screen background to Black
      static lv_style_t style_screen;
      // LV_STYLE_BG_COLOR
      lv_style_set_bg_color(&style_screen, LV_STATE_DEFAULT, LV_COLOR_BLACK);
      lv_obj_add_style(lv_scr_act(),LV_OBJ_PART_MAIN, &style_screen);

      static lv_style_t style1;
      static lv_style_t style2;
      lv_style_set_bg_color(&style1, LV_STATE_DEFAULT, LV_COLOR_BLACK);
      lv_style_set_bg_color(&style1, LV_STATE_PRESSED, LV_COLOR_GRAY);
      lv_style_set_bg_color(&style2, LV_STATE_CHECKED | LV_STATE_FOCUSED | LV_STATE_DEFAULT, LV_COLOR_PURPLE);
      static lv_style_t style3;
      lv_style_set_bg_color(&style3, LV_STATE_CHECKED | LV_STATE_FOCUSED | LV_STATE_DEFAULT, LV_COLOR_RED);

      // Create the auton button matrix
      autonBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_one_check(autonBtnm, true);
      lv_btnmatrix_set_map(autonBtnm, btnmMap);
      lv_btnmatrix_set_focused_btn(autonBtnm, AUTON_SELECTOR_DEFAULT);
      lv_btnmatrix_set_btn_ctrl(autonBtnm, AUTON_SELECTOR_DEFAULT, LV_BTNMATRIX_CTRL_CHECK_STATE);
      lv_obj_set_size(autonBtnm, 400, 40);
      lv_obj_set_pos(autonBtnm, 0, 0);
      lv_obj_align(autonBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 10);
      lv_obj_set_event_cb(autonBtnm, btnmAutonEventHandler);
      lv_obj_add_style(autonBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(autonBtnm,LV_BTNMATRIX_PART_BTN, &style2);

      // Create the Red/Blue button matrix
      colorBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_one_check(colorBtnm, true);
      lv_btnmatrix_set_map(colorBtnm, btnmMapRedBlue);
      lv_btnmatrix_set_focused_btn(colorBtnm, 0);
      lv_btnmatrix_set_btn_ctrl(colorBtnm, 0, LV_BTNMATRIX_CTRL_CHECK_STATE);
      lv_obj_set_size(colorBtnm, 400, 40);
      lv_obj_set_pos(colorBtnm, 0, 0);
      lv_obj_align(colorBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 60);
      lv_obj_set_event_cb(colorBtnm, btnmColorEventHandler);
      lv_obj_add_style(colorBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(colorBtnm,LV_BTNMATRIX_PART_BTN, &style3);

      // Create the Left/Right side button matrix
      sideBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_one_check(sideBtnm, true);
      lv_btnmatrix_set_map(sideBtnm, btnmMapLeftRight);
      lv_btnmatrix_set_focused_btn(sideBtnm, 0);
      lv_btnmatrix_set_btn_ctrl(sideBtnm, 0, LV_BTNMATRIX_CTRL_CHECK_STATE);
      lv_obj_set_size(sideBtnm, 400, 40);
      lv_obj_set_pos(sideBtnm, 0, 0);
      lv_obj_align(sideBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 110);
      lv_obj_set_event_cb(sideBtnm, btnmSideEventHandler);
      lv_obj_add_style(sideBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(sideBtnm,LV_BTNMATRIX_PART_BTN, &style2);

      // Create the Arcade/Tank button matrix
      driveBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_one_check(driveBtnm, true);
      lv_btnmatrix_set_map(driveBtnm, btnmMapArcadeTank);
      lv_btnmatrix_set_focused_btn(driveBtnm, 0);
      lv_btnmatrix_set_btn_ctrl(driveBtnm, 0, LV_BTNMATRIX_CTRL_CHECK_STATE);
      lv_obj_set_size(driveBtnm, 400, 40);
      lv_obj_set_pos(driveBtnm, 0, 0);
      lv_obj_align(driveBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 160);
      lv_obj_set_event_cb(driveBtnm, btnmSideEventHandler);
      lv_obj_add_style(driveBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(driveBtnm,LV_BTNMATRIX_PART_BTN, &style2);
    }

  } // namespace ui
} // namespace vpi