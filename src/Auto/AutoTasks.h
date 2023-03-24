#pragma once
#include "../Robot.h"
#include "Turn.h"
#include "Drive.h"

class ReadyToFire : public AutoTask
{
private:
	float rpm;

public:
	ReadyToFire(float rpm)
	{
		this->rpm = rpm;
	}
	
	void run() override
	{
		robot->flywheel->setTargetRPM(rpm);
		robot->diskLift->readyToFire();
		std::cout << "readyToFire" << std::endl;
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class Fire : public AutoTask
{
public:
	Fire()
	{}
	
	void run() override
	{
		robot->diskLift->fire();
		std::cout << "Firing" << std::endl;
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class Load : public AutoTask
{
public:
	Load()
	{}
	
	void run() override
	{
		robot->diskLift->load();
		std::cout << "Loading" << std::endl;
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class DriveIntake : public AutoTask
{
private:
	int16_t speed;

public:
	DriveIntake(int16_t speed)
	{
		this->speed = speed;
	}
	
	void run() override
	{
		robot->intake->setDrivePower(speed);
		robot->intake->on();
		std::cout << "Roller" << std::endl;
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class IntakeOff : public AutoTask
{
public:
	IntakeOff()
	{}
	
	void run() override
	{
		robot->intake->off();
		std::cout << "Roller" << std::endl;
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class Wait : public AutoTask
{
public:
	Wait()
	{}
	
	void run() override
	{
		std::cout << "Done" << std::endl;
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class DriveLeft : public AutoTask
{
private:
	int16_t speed;

public:
	DriveLeft(int16_t speed)
	{
		this->speed = speed;
	}
	
	void run() override
	{
		robot->left->moveVelocity(speed);
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class DriveRight : public AutoTask
{
private:
	int16_t speed;

public:
	DriveRight(int16_t speed)
	{
		this->speed = speed;
	}
	
	void run() override
	{
		robot->right->moveVelocity(speed);
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class DriveForward : public AutoTask
{
private:
	int16_t speed;

public:
	DriveForward(int16_t speed)
	{
		this->speed = speed;
	}
	
	void run() override
	{
		robot->right->moveVelocity(speed);
		robot->left->moveVelocity(speed);
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class FireExpansion : public AutoTask
{
private:

public:
	FireExpansion()
	{
	}
	
	void run() override
	{
		robot->expansion->fire();
		setToDone();
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};

class CorrectRoller : public AutoTask
{
private:
	
	
public:
	CorrectRoller()
	{
	}
	
	void run() override
	{
		
	}
	
	void update() override
	{
	}
	
	void exit() override
	{
	}
};
