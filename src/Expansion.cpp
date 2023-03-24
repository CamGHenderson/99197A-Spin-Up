#include "Expansion.h"

Expansion::Expansion(char port)
{
	piston = new pros::ADIDigitalOut(port);
	piston->set_value(false);
}

Expansion::~Expansion()
{
	delete piston;
}

void Expansion::fire()
{
	piston->set_value(true);
}
