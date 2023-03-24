#pragma once
#include "main.h"
#include "../Robot.h"

class AutoTask
{
protected:
	Robot* robot;
	QTime delta;

private:
	uint64_t time;	
	bool done;

public:
	AutoTask();
	
	void setTime(uint64_t time);
	void setRobot(Robot* robot);
	
	uint16_t getTime() { return time; }
	void setToDone();
	void reset();
	bool isDone() { return done; }
	
	void setDelta(QTime time);
	
	virtual void run() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;
};
