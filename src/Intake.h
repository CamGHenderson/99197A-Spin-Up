#pragma once
#include "main.h"

class Intake
{
private:
	MotorGroup* motors;
	bool running;
	int16_t drivePower;
public:
	Intake(uint8_t port);
	Intake(MotorGroup& motors);
	~Intake();
	
	void setDrivePower(int16_t drivePower);
	void setDriveDirection(int16_t direction);
	void reverse();
	
	void on();
	void off();
	
	bool isRunning() { return running; } 
	int16_t getSpeed();
	int16_t getTemp();
};
