#pragma once
#include "main.h"

#include "Flywheel.h"
#include "Intake.h"
#include "DiskLift.h"
#include "Expansion.h"

#define INTAKE_PORT -13

// in question
#define LIFT_PORT -17
#define LIFT_LIMIT_PORT 'D'

#define FLYWHEEL_PORT_1 11
#define FLYWHEEL_PORT_2 12

#define EXPANSION_PORT 'H'

#define LEFT_DRIVE_PORT_1 1
#define LEFT_DRIVE_PORT_2 2

#define RIGHT_DRIVE_PORT_1 -8
#define RIGHT_DRIVE_PORT_2 -9

// TODO measure wheel base, probably not accurate
#define WHEEL_DIAMETER 4_in
#define DRIVE_RATIO 1
#define WHEEL_BASE 13.125_in
#define WHEEL_TRACK 12_in

namespace Subsystems
{
	std::vector<Motor> initializeDriveMotors();
	std::shared_ptr<ChassisController> initializeChassisController(std::vector<Motor>& driveMotors);
	Intake* initializeIntake();
	Flywheel* initializeFlywheel(uint8_t loopDelay);
	DiskLift* initializeDiskLift();
	Expansion* initializeExpansion();
}




