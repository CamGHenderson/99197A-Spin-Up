#pragma once
#include "AutoTask.h"

class Turn : public AutoTask
{
private:
	double targetAngle;
	double initialAngle;
	double currentAngle;
	double lastAngle;
	int16_t fullTurn;
	int8_t direction;
	
	int16_t rpm;
	int16_t maxRPM;
	int16_t topRPM;
	int16_t rpmStep;
	
	float totalTime;
	float proportionalGain; 
	
	uint16_t logCount;
	
public:
	Turn(double angle);
	
	void run() override;
	
private:
	double getAngle();
	
public:
	void update() override;
	void exit() override;
};

