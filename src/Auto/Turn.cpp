#include "Turn.h"

Turn::Turn(double angle)
{
	targetAngle = angle;
	if(angle < 0)
		direction = -1;
	else
		direction = 1;
}

void Turn::run()
{
	pros::Imu imu(robot->imuPort);
	initialAngle = imu.get_heading();
	std::cout << "Initial Angle: " << initialAngle << std::endl;
	
	currentAngle = initialAngle;
	lastAngle = initialAngle;
	fullTurn = 0;
	
	
	// TODO: adjust turning speeds below 180 degrees (180 is decently tuned)
	if(abs(targetAngle) >= 180)
	{
		rpm = 0;
		maxRPM = 200;
		proportionalGain = 1.5;
		topRPM = -1;
		rpmStep = 2;
	}
	else if(abs(targetAngle) >= 90)
	{
		rpm = 0;
		maxRPM = 50;
		
		proportionalGain = 1;
		
		topRPM = -1;
		rpmStep = 2;
	}
	else
	{
		rpm = 0;
		maxRPM = 30;
		
		proportionalGain = 1;
		
		topRPM = -1;
		rpmStep = 2;
	}
	
	totalTime = 0.0f;
	logCount = 0;
}

double Turn::getAngle()
{
	pros::Imu imu(robot->imuPort);

	double rawCurrentAngle = imu.get_heading();
	
	if(((int16_t)rawCurrentAngle) - lastAngle < (-340))
	{
		fullTurn++;
	}
	else if(((int16_t)rawCurrentAngle) - lastAngle > (340))
		fullTurn--;
	lastAngle = rawCurrentAngle;

	return (rawCurrentAngle + (fullTurn * 360.0)) - initialAngle;
}

void Turn::update()
{
	float deltaTime = (float)(delta.getValue());
	totalTime += deltaTime;
	
	currentAngle = getAngle();
	
	if(abs(currentAngle) < (abs(targetAngle) / 2.0))
	{
		// accelerate robot for inital component of turn
		rpm += rpmStep;
		topRPM = rpm;
	}
	else
	{
		// slow down for accurate angle
		double error = abs(targetAngle) - abs(currentAngle);
		rpm = error * proportionalGain;
		if(rpm > topRPM)
			rpm = topRPM;
	}
	
	// protection against unallowed rpms
	if(rpm > maxRPM)
		rpm = maxRPM;
	else if(rpm < 0)
		rpm = 0;
	
	if(abs(currentAngle) > (abs(targetAngle) - 1.0) && rpm == 0)
	{
		std::cout << "done turn at " << currentAngle << " degrees" << std::endl;
		robot->left->moveVelocity(0);
		robot->right->moveVelocity(0);
		setToDone();
	}
	
	// update rpms
	robot->left->moveVelocity(rpm * direction);
	robot->right->moveVelocity(-rpm * direction);
	
	// angle logging
	logCount++;
	if(logCount > 50)
	{
		std::cout << currentAngle << std::endl;
		logCount = 0;
	}
}

void Turn::exit()
{
}
