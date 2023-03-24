#include "Subsystems.h"

std::vector<Motor> Subsystems::initializeDriveMotors()
{
	return { LEFT_DRIVE_PORT_1, LEFT_DRIVE_PORT_2, RIGHT_DRIVE_PORT_1, RIGHT_DRIVE_PORT_2 };
}

std::shared_ptr<ChassisController> Subsystems::initializeChassisController(std::vector<Motor>& driveMotors)
{
	return ChassisControllerBuilder()
		   .withMotors({ driveMotors[0], driveMotors[1] },
		    		   { driveMotors[2], driveMotors[3] })
		   .withDimensions({ AbstractMotor::gearset::green, (DRIVE_RATIO) },
		   { { WHEEL_DIAMETER, WHEEL_TRACK }, imev5GreenTPR })
		   .build();
}

Intake* Subsystems::initializeIntake()
{
	return new Intake(INTAKE_PORT);
}

Flywheel* Subsystems::initializeFlywheel(uint8_t loopDelay)
{
	MotorGroup* flywheelMotors = new MotorGroup { FLYWHEEL_PORT_1, FLYWHEEL_PORT_2 };
	return new Flywheel(flywheelMotors, loopDelay);
}

DiskLift* Subsystems::initializeDiskLift()
{
	return new DiskLift(LIFT_PORT, LIFT_LIMIT_PORT);
}

Expansion* Subsystems::initializeExpansion()
{
	return new Expansion(EXPANSION_PORT);
}
