#pragma once

#include "main.h"

class Flywheel
{
private:
	enum class Instruction
	{
		SPIN_UP,
		SLOW_DOWN,
		CLEAR
	};

	MotorGroup* motors;
	Instruction instruction;
	uint8_t loopDelay;
	bool running;
	float targetSpeed;
	
public:
	Flywheel(MotorGroup* motors, uint8_t loopDelay);
	~Flywheel();
	
	void speedUp();
	void slowDown();
	void update();
	void setTargetRPM(int16_t speed);
	
	int16_t getSpeed();
	int16_t getTargetSpeed();
	int16_t getTemp();
	
	bool isRunning() { return running; }
};
