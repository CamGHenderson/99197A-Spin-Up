#pragma once
#include "main.h"
#include "Flywheel.h"
#include "Intake.h"

class ControllerDisplayLayer
{
private:
	static Controller* masterController;
	static Controller* partnerController;
	static std::string msg;
	static bool first;
	static uint16_t timeCount;
	static bool tempWarn;
	static uint16_t rumbleCount;
	static uint16_t highTemp;

public:
	static void initialize(Controller& masterController, Controller& partnerController);
	static void update(std::vector<Motor>& driveMotors, Flywheel* flywheel, Intake* intake);
	static void fuckYou();
};
