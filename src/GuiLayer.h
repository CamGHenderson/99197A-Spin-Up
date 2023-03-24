#pragma once
#include "main.h"
#include "Auto/AutoProgram.h"

#define NONE 0
#define CLOSE_AUTO 1
#define FAR_AUTO 2
#define AUTO_SKILLS 3

class GuiLayer
{
private:
	static uint16_t selection;
	static uint8_t color;
	static lv_obj_t* blueBtn;
	static lv_obj_t* redBtn;
	
public:
	static void displayTest();
	
private:
	static void createButton();
	static lv_res_t selectCloseAuto(lv_obj_t* btn);
	static lv_res_t selectFarAuto(lv_obj_t* btn);
	static lv_res_t selectAutoSkills(lv_obj_t* btn);
	static lv_res_t selectBlue(lv_obj_t* btn);
	static lv_res_t selectRed(lv_obj_t* btn);

public:
	static void displayAutoMenu();
	static uint16_t getSelection() { return selection; }
	static uint8_t getColor() { return color; };
};
