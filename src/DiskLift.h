#pragma once 
#include "main.h"
#include "Flywheel.h"

// TODO need to get rid of limit switch, is unnessary
class DiskLift
{
public:
	
	enum class LiftState
	{
		LOADING,
		READY_TO_FIRE,
		FIRING,
		MANUAL
	};
	
private:
	Motor* motor;
	
	LiftState state;
	bool flywheelReady;
	
	ADIButton limit = ADIButton('D', false);
	ADIButton swingBar = ADIButton('G', false);
	ADIButton diskSwitch = ADIButton('B', false);
	ADIButton upperLimit = ADIButton('E', false);
	int16_t temp;
	
	float diskCount;
	
public:
	DiskLift(int8_t motorPort, char limitPort);
	~DiskLift();
	
	void update(Flywheel* flywheel);
	void home();

private:
	void internalMove(int8_t direction);
	void slowInternalMove(int8_t direction);

public:
	void move(int8_t direction);
	
	void load();
	void readyToFire();
	void fire();
	void manual();
	
	void setDiskAmount(uint16_t diskCount) { this->diskCount = diskCount; }
	uint16_t getDiskAmount() { return diskCount; }
	
	bool safeForExpansion();
	
	LiftState getState() { return state; }
};
