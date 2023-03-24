#include "DiskLift.h"

#define UP 1
#define DOWN -UP

// TODO Lower after 3 disks shot

// TODO optimise these values
// TODO Fix ready to fire position, probably not correct
#define READY_TO_FIRE_POSITION 2
#define MAX_HEIGHT 5

// used to figure out when disk has been shot
#define DISK_FIRED_RPM 2000
#define RPM_FIRE_LOSS 300

// rpm required to fire disk
#define MIN_FIRE_RPM 1700

DiskLift::DiskLift(int8_t motorPort, char limitPort)
{
	motor = new Motor(motorPort);
	motor->setBrakeMode(AbstractMotor::brakeMode::hold);
	motor->setEncoderUnits(AbstractMotor::encoderUnits::rotations);
	motor->setGearing(AbstractMotor::gearset::green);
	
	state = LiftState::LOADING;
	flywheelReady = false;
	temp = 0;
	
	diskCount = 0;
}

DiskLift::~DiskLift()
{
	delete motor;
}

void DiskLift::update(Flywheel* flywheel)
{
	if(((state != LiftState::READY_TO_FIRE) && (state != LiftState::FIRING)) && flywheel->isRunning())
		flywheel->slowDown();
	
	flywheelReady = flywheel->isRunning();
	
	double pos = motor->getPosition();
	
	if(limit.changedToPressed())
	{
		std::cout << "at home position" << std::endl;
	}
	
	switch(state)
	{
		case LiftState::LOADING:
		{
			if(!limit.isPressed())
				internalMove(DOWN);
			else
				internalMove(0);
		
			break;
		}
		
		case LiftState::READY_TO_FIRE:
		{
			if(!flywheel->isRunning())
				flywheel->speedUp();
		
			if(pos < READY_TO_FIRE_POSITION)
				internalMove(UP);
			else
				internalMove(0);
			
			if(upperLimit.isPressed())
			{
				diskCount = 0;
				state = LiftState::LOADING;
				//std::cout << "Upper Limit Pressed" << std::endl;
			}
			
			break;
		}
		
		case LiftState::FIRING:
		{
			if((flywheel->getSpeed() <= flywheel->getTargetSpeed() - RPM_FIRE_LOSS) || (pos >= MAX_HEIGHT))
			{
				diskCount--;
				if(diskCount < 0)
				{
					diskCount = 0;
					std::cout << "Bad Person" << std::endl;
					std::cout << "Disk Count: " << diskCount << std::endl << std::endl;
				}
				state = LiftState::READY_TO_FIRE;
			}
			
			if(upperLimit.isPressed())
			{
				diskCount = 0;
				state = LiftState::LOADING;
			}
			
			if(flywheel->getSpeed() >= MIN_FIRE_RPM)
				internalMove(UP);
				
			break;
		}
		
		case LiftState::MANUAL:
		{
			break;
		}
	}
	
	// display temp reading whenever it has changed
	int16_t newTemp = motor->getTemperature();
	if(temp != newTemp)
	{
		temp = newTemp;
		std::cout << "Lift new temp: " << temp << std::endl;
	}
	
	if(diskSwitch.changedToPressed())
	{
		diskCount += .5;
		std::cout << "Disk Count: " << diskCount << std::endl;
	}
}

void DiskLift::home()
{
	motor->tarePosition();
}

void DiskLift::slowInternalMove(int8_t direction)
{
	motor->moveVoltage(6000 * direction * UP);
}

void DiskLift::internalMove(int8_t direction)
{
	motor->moveVoltage(12000 * direction * UP);
}

void DiskLift::move(int8_t direction)
{
	if(state == LiftState::MANUAL)
		internalMove(direction);
}

void DiskLift::load()
{
	state = LiftState::LOADING;
}

void DiskLift::readyToFire()
{
	state = LiftState::READY_TO_FIRE;
}

void DiskLift::fire()
{
	if(state == LiftState::READY_TO_FIRE && flywheelReady)
		state = LiftState::FIRING;
}

void DiskLift::manual()
{
	state = LiftState::MANUAL;
}

bool DiskLift::safeForExpansion()
{
	double pos = motor->getPosition();
	return (state == LiftState::LOADING && limit.isPressed());
}
