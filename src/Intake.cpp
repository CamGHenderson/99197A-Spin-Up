#include "Intake.h"

Intake::Intake(uint8_t port)
{
	motors = new MotorGroup({ (int8_t)port });
	motors->setBrakeMode(AbstractMotor::brakeMode::hold);
	drivePower = 12000;
	running = false;
}

Intake::Intake(MotorGroup& motors)
{
	this->motors = &motors;
	this->motors->setBrakeMode(AbstractMotor::brakeMode::hold);
	drivePower = 12000;
	running = false;
}

Intake::~Intake()
{
	delete motors;
}

void Intake::setDrivePower(int16_t drivePower)
{
	this->drivePower = drivePower;
	
	// update direction if motor already running
	if(running)
		motors->moveVoltage(this->drivePower);
}

void Intake::setDriveDirection(int16_t direction)
{
	this->drivePower = direction * 12000;
	
	// update direction if motor already running
	if(running)
		motors->moveVoltage(this->drivePower);
}

void Intake::reverse()
{
	drivePower = -drivePower;
}

void Intake::on()
{
	running = true;
	motors->moveVoltage(drivePower);
}

void Intake::off()
{
	running = false;
	motors->moveVoltage(0);
}

int16_t Intake::getSpeed()
{
	return motors->getActualVelocity() * 3.0f;
}

int16_t Intake::getTemp()
{
	return motors->getTemperature();
}
