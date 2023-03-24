#pragma once
#include "Subsystems.h"

struct Robot
{
	std::vector<Motor> driveMotors;
	Flywheel* flywheel;
	Intake* intake;
	DiskLift* diskLift;
	std::shared_ptr<ChassisController> drive;
	Expansion* expansion;
	MotorGroup* left;
	MotorGroup* right;
	
	OpticalSensor* opticalSensor;
	uint8_t imuPort;
};
