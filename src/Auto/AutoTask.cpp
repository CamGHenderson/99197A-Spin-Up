#include "AutoTask.h"

AutoTask::AutoTask()
{
	done = false;
}

void AutoTask::setTime(uint64_t time)
{
	this->time = time;
}

void AutoTask::setRobot(Robot* robot)
{
	this->robot = robot;
}

void AutoTask::setDelta(QTime time)
{
	this->delta = time;
}

void AutoTask::setToDone()
{
	done = true;
}

void AutoTask::reset()
{
	done = false;
}
