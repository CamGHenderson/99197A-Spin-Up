#include "AutoSkills.h"
#include "AutoTasks.h"

AutoSkills::AutoSkills(Robot& robot, uint8_t color) : AutoProgram(robot)
{
	std::cout << "Autonomous Skills" << std::endl;
	
	shootFirstVolley();
	initialReverse();
	
	alignToThreeLine();
	collectThreeLine();
	readySecondVolley();
	shootSecondVolley();
	
	alignFirstThreeStack();
	collectFirstThreeStack();
	readyThirdVolley();
	shootThirdVolley();
	
	alignSecondThreeStack();
	collectSecondThreeStack();
	readyForthVolley();
	shootForthVolley();
	
	moveToExpansionPosition();
	expand();
}

void AutoSkills::shootFirstVolley()
{
	addTask(new ReadyToFire(1875), 0);
	addTask(new Fire(), 1800);
	addTask(new Fire(), 1800);
}

void AutoSkills::initialReverse()
{
	addTask(new DriveForward(-40), 1500);
	addTask(new DriveForward(-50), 200);
	addTask(new DriveForward(-70), 200);
	addTask(new DriveForward(-80), 200);
	addTask(new DriveForward(-90), 200);
	addTask(new Load(), 0);
	addTask(new DriveForward(0), 1100);
}

void AutoSkills::alignToThreeLine()
{
	addTask(new Turn(58), 750);
}

void AutoSkills::collectThreeLine()
{
	addTask(new DriveForward(40), 3250);
	addTask(new DriveIntake(12000), 0);
	
	addTask(new DriveForward(50), 200);
	
	addTask(new DriveForward(70), 200);
	addTask(new DriveForward(80), 200);
	addTask(new DriveForward(90), 200);
	addTask(new DriveForward(100), 200);
	addTask(new DriveForward(110), 200);
	addTask(new DriveForward(120), 200);
	addTask(new DriveForward(0), 1200);
	addTask(new IntakeOff, 1000);
}

void AutoSkills::readySecondVolley()
{
	addTask(new ReadyToFire(2105), 0);
	addTask(new Turn(-120), 0);
}

void AutoSkills::shootSecondVolley()
{
	addTask(new Fire(), 3500);
	addTask(new Fire(), 1500);
	addTask(new Fire(), 1500);
	addTask(new Load(), 1600);
}

void AutoSkills::alignFirstThreeStack()
{
	addTask(new Turn(110), 0);
}

void AutoSkills::collectFirstThreeStack()
{
	addTask(new DriveIntake(12000), 0);
	addTask(new DriveForward(40), 3000);
	addTask(new DriveForward(50), 200);
	addTask(new DriveForward(70), 200);
	addTask(new DriveForward(80), 200);
	addTask(new DriveForward(0), 1500);
	addTask(new IntakeOff, 1400);
}

void AutoSkills::readyThirdVolley()
{
	addTask(new Turn(-142), 0);	
	addTask(new ReadyToFire(2200), 0);
}

void AutoSkills::shootThirdVolley()
{
	addTask(new Fire(), 3500);
	addTask(new Fire(), 2000);
	addTask(new Fire(), 2000);
	addTask(new Load(), 1500);
}

void AutoSkills::alignSecondThreeStack()
{
	addTask(new Turn(-140), 0);	
}

void AutoSkills::collectSecondThreeStack()
{
	addTask(new DriveIntake(12000), 0);
	addTask(new DriveForward(40), 3000);
	addTask(new DriveForward(50), 200);
	addTask(new DriveForward(70), 200);
	addTask(new DriveForward(80), 200);
	addTask(new DriveForward(0), 1500);
	addTask(new IntakeOff, 1400);
}

void AutoSkills::readyForthVolley()
{
	addTask(new Turn(45), 0);
	addTask(new ReadyToFire(2275), 0);
}

void AutoSkills::shootForthVolley()
{
	addTask(new Fire(), 3500);
	addTask(new Fire(), 2000);
	addTask(new Fire(), 2000);
	addTask(new Load(), 1500);
}


void AutoSkills::moveToExpansionPosition()
{
	addTask(new DriveForward(-80), 0);
	addTask(new DriveForward(0), 885);
	
	addTask(new Turn(61), 0);
	
	addTask(new DriveForward(-100), 3250);
	addTask(new DriveForward(0), 300);
}

void AutoSkills::expand()
{
	addTask(new FireExpansion(), 800);
}

void AutoSkills::addSmoothAcceleration(int16_t startRPM, int16_t endRPM, uint16_t delay, uint16_t startTime)
{
	uint16_t steps = (endRPM / 10) - (startRPM / 10);
	
	addTask(new DriveForward(startRPM), startTime);
	for(uint8_t i = 1; i < steps; i++)
	{
		addTask(new DriveForward(startRPM + (i * 10)), delay);
	}
}

/* old program revert if broken
#include "AutoSkills.h"
#include "AutoTasks.h"

AutoSkills::AutoSkills(Robot& robot, uint8_t color) : AutoProgram(robot)
{
	std::cout << "Auto Skills" << std::endl;
	
	// first volley
	addTask(new ReadyToFire(1875), 0);
	addTask(new Fire(), 1800);
	addTask(new Fire(), 1800);
	
	std::cout << "First Volley Complete" << std::endl;
	
	addTask(new DriveForward(-40), 1500);
	addTask(new DriveForward(-50), 200);
	addTask(new DriveForward(-70), 200);
	addTask(new DriveForward(-80), 200);
	addTask(new DriveForward(-90), 200);
	addTask(new Load(), 0);
	addTask(new DriveForward(0), 1100);
	
	addTask(new Turn(58), 750);
	
	addTask(new DriveForward(40), 3250);
	addTask(new DriveIntake(12000), 0);
	addTask(new DriveForward(50), 200);
	addTask(new DriveForward(70), 200);
	addTask(new DriveForward(80), 200);
	addTask(new DriveForward(90), 200);
	addTask(new DriveForward(100), 200);
	addTask(new DriveForward(110), 200);
	addTask(new DriveForward(120), 200);
	addTask(new DriveForward(0), 1200);
	addTask(new IntakeOff, 1000);
	addTask(new ReadyToFire(2105), 0);
	addTask(new Turn(-120), 0);
	
	addTask(new Fire(), 3500);
	addTask(new Fire(), 1500);
	addTask(new Fire(), 1500);
	addTask(new Load(), 1600);
	std::cout << "Second Volley Complete" << std::endl;
	
	addTask(new Turn(110), 0);
	addTask(new DriveIntake(12000), 0);
	addTask(new DriveForward(40), 3000);
	addTask(new DriveForward(50), 200);
	addTask(new DriveForward(70), 200);
	addTask(new DriveForward(80), 200);
	addTask(new DriveForward(0), 1500);
	addTask(new IntakeOff, 1400);
	
	addTask(new Turn(-142), 0);
	
	addTask(new ReadyToFire(2200), 0);
	addTask(new Fire(), 3500);
	addTask(new Fire(), 2000);
	addTask(new Fire(), 2000);
	addTask(new Load(), 1500);
	std::cout << "Third Volley Complete" << std::endl;
	
	addTask(new Turn(-140), 0);
	
	addTask(new DriveIntake(12000), 0);
	addTask(new DriveForward(40), 3000);
	addTask(new DriveForward(50), 200);
	addTask(new DriveForward(70), 200);
	addTask(new DriveForward(80), 200);
	addTask(new DriveForward(0), 1500);
	addTask(new IntakeOff, 1400);
	
	// turn in question
	addTask(new Turn(45), 0);
	
	addTask(new ReadyToFire(2300), 0);
	addTask(new Fire(), 3500);
	addTask(new Fire(), 2000);
	addTask(new Fire(), 2000);
	addTask(new Load(), 1500);
	std::cout << "Forth Volley Complete" << std::endl;
	
	// TODO Increase back tiny bit
	// 40rpm for 2000ms works
	addTask(new DriveForward(-80), 0);
	addTask(new DriveForward(0), 850);
	addTask(new Turn(58), 0);
	
	addTask(new DriveForward(-100), 3250);
	addTask(new DriveForward(0), 300);
	
	addTask(new FireExpansion(), 800);
	std::cout << "Forth Volley Complete" << std::endl;
}*/


