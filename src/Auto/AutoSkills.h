#pragma once
#include "AutoProgram.h"

class AutoSkills : public AutoProgram
{
public:
	AutoSkills(Robot& robot, uint8_t color);
	
private:
	void shootFirstVolley();
	void initialReverse();
	void alignToThreeLine();
	void collectThreeLine();
	void readySecondVolley();
	void shootSecondVolley();
	void alignFirstThreeStack();
	void collectFirstThreeStack();
	void readyThirdVolley();
	void shootThirdVolley();
	void alignSecondThreeStack();
	void collectSecondThreeStack();
	void readyForthVolley();
	void shootForthVolley();
	void moveToExpansionPosition();
	void expand();
	
	void addSmoothAcceleration(int16_t startRPM, int16_t endRPM, uint16_t delay, uint16_t startTime);
};
