#pragma once
#include "../Robot.h"
#include "AutoTask.h"

#define RED 1
#define BLUE 2

class AutoProgram
{
protected:
	std::vector<AutoTask*> tasks;
	std::vector<AutoTask*> runningTasks;

	Robot* robot;
	MotorGroup* left;
	MotorGroup* right;
	
	double estimatedTime;

public:
	AutoProgram(Robot& robot);
	~AutoProgram();
	
	void addTask(AutoTask* task, uint64_t time);
	void run();
	double getEstimatedTime();
	
protected:
	void fireDisks(uint8_t amount);
	void updateSystems();
};
