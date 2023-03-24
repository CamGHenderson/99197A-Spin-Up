#pragma once

#include "AutoTask.h"

class Drive : public AutoTask
{
private:
	int32_t currentTime;
	int32_t endTime;
	
	int16_t maxRPM;
	int16_t leftRPM;
	int16_t rightRPM;
	int16_t rpmStep;
	
public:
	Drive();
	
	void run() override;
	void update() override;
	void exit() override;

};
