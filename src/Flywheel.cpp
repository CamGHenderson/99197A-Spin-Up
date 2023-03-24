#include "Flywheel.h"

#define SLOW_DOWN_TIME 5000
#define MAX_FLYWHEEL_VOLTAGE 12000
#define MAX_FLYWHEEL_RPM 200.0

#define PID_RPM_CONTROL 0
#define PROPORTIONAL_GAIN 1

#define kP 2.0
#define kD .01

Flywheel::Flywheel(MotorGroup* motors, uint8_t loopDelay)
{
	this->motors = motors;
	instruction = Instruction::CLEAR;
	this->loopDelay = loopDelay;
	running = false;
	targetSpeed = 200;
}

Flywheel::~Flywheel()
{
	delete motors;
}
 
void Flywheel::speedUp()
{
	if(!running)
		instruction = Instruction::SPIN_UP;
}

void Flywheel::slowDown()
{
	if(running)
		instruction = Instruction::SLOW_DOWN;
}

void Flywheel::update()
{
	static uint16_t slowDownStep;
	switch (instruction)
	{
		case Instruction::SPIN_UP:
		{
			if(!PID_RPM_CONTROL)
				motors->moveVelocity(targetSpeed);
			
			running = true;
			instruction = Instruction::CLEAR;
			
			break;
		}	
		case Instruction::SLOW_DOWN:
		
			if(running)
			{
				running = false;
				slowDownStep = SLOW_DOWN_TIME;
			}
		
			slowDownStep -= loopDelay;
			
			if(slowDownStep >= 0)
			{
				if(!PID_RPM_CONTROL)
					motors->moveVelocity(0);
				
				instruction = Instruction::CLEAR;
			}
			else
			{
				if(!PID_RPM_CONTROL)
					motors->moveVoltage((MAX_FLYWHEEL_VOLTAGE) * (slowDownStep / SLOW_DOWN_TIME));
			}
			
			break;
		
		case Instruction::CLEAR:
			
			break;
	};
}

void Flywheel::setTargetRPM(int16_t speed)
{
	targetSpeed = ((float)(speed)) / 15.0f;
	
	if(running)
	{
		if(!PID_RPM_CONTROL)
			motors->moveVelocity(targetSpeed);
	}
}

int16_t Flywheel::getSpeed()
{
	return motors->getActualVelocity() * 15.0f;
}

int16_t Flywheel::getTargetSpeed()
{
	return motors->getTargetVelocity() * 15.0f;
}

int16_t Flywheel::getTemp()
{
	return motors->getTemperature();
}


