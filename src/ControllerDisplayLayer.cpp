#include "ControllerDisplayLayer.h"

#define MSG1 "Fuck You!      "
#define MSG2 "Im Underground!"

#define OVER_TEMP 30

Controller* ControllerDisplayLayer::masterController = nullptr;
Controller* ControllerDisplayLayer::partnerController = nullptr;
std::string ControllerDisplayLayer::msg;
bool ControllerDisplayLayer::first = false;
uint16_t ControllerDisplayLayer::timeCount = 0;
bool masterControllerUpdate = true;

void ControllerDisplayLayer::initialize(Controller& masterController, Controller& partnerController)
{
	ControllerDisplayLayer::masterController = &masterController;
	ControllerDisplayLayer::partnerController = &partnerController;
}

void ControllerDisplayLayer::update(std::vector<Motor>& driveMotors, Flywheel* flywheel, Intake* intake)
{
	if(flywheel->isRunning())
	{
		msg = std::to_string(flywheel->getSpeed()) + "RPM    " + std::to_string(flywheel->getTemp()) + "C";
	}
	else if(intake->isRunning())
	{
		msg = std::to_string(intake->getSpeed()) + "RPM    " + std::to_string(intake->getTemp()) + "C";
	}
	else
	{
		std::string temps[4];
		for(uint8_t i = 0; i < driveMotors.size(); i++)
		{
			int16_t temp = (int16_t)driveMotors[i].getTemperature();
			temps[i] = std::to_string(temp);
		}
		msg = "L" + temps[0] + " " + temps[1] + " R " + temps[2] + " " + temps[3];
	}
	
	if(masterControllerUpdate)
	{
		masterController->setText(0, 0, msg);
		masterControllerUpdate = false;
	}
	else
	{
		partnerController->setText(0, 0, msg);
		masterControllerUpdate = true;
	}
}

void ControllerDisplayLayer::fuckYou()
{
	if(timeCount < 1000)
		timeCount++;
	else
	{
		msg = (first) ? MSG2 : MSG1; 
		masterController->setText(0, 0, msg);
		timeCount = 0;
		first = !first;
	}
}
