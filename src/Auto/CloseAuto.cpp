#include "CloseAuto.h"
#include "AutoTasks.h"

CloseAuto::CloseAuto(Robot& robot, uint8_t color) : AutoProgram(robot)
{
	// entire close program ends at 13.15 seconds
	std::cout << "Close Auto" << std::endl;
	
	addTask(new ReadyToFire(2600), 0);
	
	addTask(new Fire(), 3000); // 3 seconds
	addTask(new Fire(), 4750); // 7.75 seconds
	addTask(new Load(), 2250); // 10 seconds
	
	addTask(new DriveRight(-100), 1000); // 11 seconds
	addTask(new DriveRight(0), 400); // 11.4 seconds
	addTask(new DriveLeft(-100), 100); // 11.5 seconds
	
	addTask(new DriveIntake(12000), 250); // 11.75 seconds
	addTask(new DriveLeft(0), 250); // 12 seconds
	addTask(new IntakeOff, 150); // 12.15 seconds
	
	addTask(new Wait(), 1000); // 13.15 seconds
}
