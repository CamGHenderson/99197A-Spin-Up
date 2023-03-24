#pragma once
#include "main.h"

class Expansion
{
private:
	pros::ADIDigitalOut* piston;
	
public:
	Expansion(char port);
	~Expansion();
	
	void fire();
};
