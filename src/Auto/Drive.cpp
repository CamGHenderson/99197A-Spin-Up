#include "Drive.h"

Drive::Drive()
{
	endTime = 2000;
	maxRPM = 100;
}

void Drive::run()
{
	currentTime = 0;
	
	leftRPM = 0;
	rightRPM = 0;
	
	rpmStep = 1;
	
}

void Drive::update()
{
	float deltaTime = (float)(delta.getValue());
	currentTime += deltaTime;
	
	if(currentTime < (endTime / 2.0))
	{
		if(leftRPM < maxRPM)
		{
			leftRPM += rpmStep;
		}
		
		if(rightRPM < maxRPM)
		{
			rightRPM += rpmStep;
		}
		
		if(leftRPM > maxRPM)
		{
			leftRPM = maxRPM;
		}
		
		if(rightRPM < maxRPM)
		{
			rightRPM = maxRPM;
		}
	}
	else
	{
		
	}
	
	robot->left->moveVelocity(leftRPM);
	robot->right->moveVelocity(rightRPM);
}

void Drive::exit()
{}
