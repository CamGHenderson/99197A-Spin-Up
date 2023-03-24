#include "FarAuto.h"
#include "AutoTasks.h"

FarAuto::FarAuto(Robot& robot, uint8_t color) : AutoProgram(robot)
{
	// fire preloads
	addTask(new ReadyToFire(2705), 0);
	addTask(new Fire(), 1250); // 1.25 seconds
	addTask(new Fire(), 3250); // 4.5 seconds
	addTask(new Load(), 500); // 5 seconds
	
	
	// initial drive forward and stop
	addTask(new DriveForward(125), 0);
	addTask(new DriveForward(0), 775); // 5.775 seconds
	
	
	// inital turn along autonomous line and stop
	addTask(new DriveLeft(-25), 525); // ~8 seconds 
	addTask(new DriveRight(25), 0);
	addTask(new DriveForward(0), 1350); // ~8.35 seconds
	
	// backwards along autonomous line and stop
	addTask(new DriveForward(-125), 150);
	addTask(new DriveForward(0), 900); // ~9 seconds
	
	// turn towards roller
	addTask(new DriveLeft(50), 1500); // ~10.5 seconds
	addTask(new DriveRight(-50), 0);
	
	// turn stop
	addTask(new DriveLeft(0), 350); // ~11 seconds
	addTask(new DriveRight(0), 0);
	
	// shift right
	addTask(new DriveRight(-25), 450);
	addTask(new DriveLeft(-50), 0);
	addTask(new DriveIntake(12000), 0); // ~11.5 seconds
	
	// 1000
	addTask(new IntakeOff, 1000);
	addTask(new DriveRight(0), 200); // ~12.6 seconds
	// 0
	addTask(new DriveLeft(0), 0);
	// 0
	
	addTask(new Wait(), 1000); // ~14 seconds
}
