#include "main.h"
#include "Subsystems.h"
#include "GuiLayer.h"
#include "ControllerDisplayLayer.h"
#include "Robot.h"
#include "Auto/AutoProgram.h"
#include "Auto/CloseAuto.h"
#include "Auto/FarAuto.h"
#include "Auto/AutoSkills.h"
#include <iostream>

#define LOOP_DELAY 10

#define COMPITETION_MODE 1

#define GARBO_RPM 3000
#define HIGH_RPM 2665

// Y button
#define MEDIUM_RPM 2350

// B button
#define MEDIUM_RPM2 2225

// X button
#define MEDIUM_RPM3 2575

// A button
#define LOW_RPM 1885

// TODO what
#define CYCLE_TIME 250

std::vector<Motor> driveMotors = Subsystems::initializeDriveMotors();
Flywheel* flywheel = Subsystems::initializeFlywheel(LOOP_DELAY);
Intake* intake = Subsystems::initializeIntake();
DiskLift* diskLift = Subsystems::initializeDiskLift();;
std::shared_ptr<ChassisController> drive = Subsystems::initializeChassisController(driveMotors);
Expansion* expansion = Subsystems::initializeExpansion();
Robot robot = { driveMotors, flywheel, intake, diskLift, drive, expansion,
			   new MotorGroup{ robot.driveMotors[0], robot.driveMotors[1]},
			   new MotorGroup{ robot.driveMotors[2], robot.driveMotors[3]} };

OpticalSensor* opticalSensor = nullptr;			   

CloseAuto* closeAuto = nullptr;
FarAuto* farAuto = nullptr;
AutoSkills* autoSkills = nullptr;
uint8_t teamColor = 0;

Controller controller(ControllerId::master);
Controller partner(ControllerId::partner);

ControllerButton intakeOn(ControllerId::master, ControllerDigital::L2);
ControllerButton diskModeToggle(ControllerId::master, ControllerDigital::L1);
ControllerButton fire(ControllerId::master, ControllerDigital::R1);
ControllerButton liftMode(ControllerId::master, ControllerDigital::R2);

ControllerButton mediumRange(ControllerId::master, ControllerDigital::Y);
ControllerButton mediumRange2(ControllerId::master, ControllerDigital::B);
ControllerButton mediumRange3(ControllerId::master, ControllerDigital::X);
ControllerButton shortRange(ControllerId::master, ControllerDigital::A);
ControllerButton longRange(ControllerId::master, ControllerDigital::right);
ControllerButton garboRange(ControllerId::master, ControllerDigital::left);

ControllerButton rollerUp(ControllerId::master, ControllerDigital::up);
ControllerButton rollerDown(ControllerId::master, ControllerDigital::down);

ControllerButton manualMode(ControllerId::partner, ControllerDigital::left);
ControllerButton diskLiftUp(ControllerId::partner, ControllerDigital::up);
ControllerButton diskLiftDown(ControllerId::partner, ControllerDigital::down);

ControllerButton expansionFire1(ControllerId::partner, ControllerDigital::R1);
ControllerButton expansionFire2(ControllerId::partner, ControllerDigital::R2);
ControllerButton expansionFire3(ControllerId::partner, ControllerDigital::L1);
ControllerButton expansionFire4(ControllerId::partner, ControllerDigital::L2);
ControllerButton expansionFire5(ControllerId::partner, ControllerDigital::left);
ControllerButton expansionFire6(ControllerId::partner, ControllerDigital::A);

ControllerButton startLogging(ControllerId::partner, ControllerDigital::B);
ControllerButton autoTest(ControllerId::partner, ControllerDigital::right);

uint16_t selection = NONE;
bool diskMode = true;
bool manualIntakeControl = false;

void initialize()
{
	// initialize controller display
	ControllerDisplayLayer::initialize(controller, partner);
	
	// set home position for lift
	diskLift->home();
	
	// wait for selection on brain display
	GuiLayer::displayAutoMenu();
	/*while(GuiLayer::getSelection() == NONE) 
	{
		pros::delay(LOOP_DELAY);
	}
	
	// get data from ui selection
	selection = GuiLayer::getSelection();*/
	selection = CLOSE_AUTO;
	
	// TODO Temp auto testing (remove when done)
	teamColor = GuiLayer::getColor();
	std::cout << GuiLayer::getSelection() << std::endl;
	
	// initialize sensors
	robot.opticalSensor = new OpticalSensor(10);
	robot.imuPort = 16;
	opticalSensor = robot.opticalSensor;
	opticalSensor->setLedPWM(100);
	
	pros::Imu imu(robot.imuPort);
	imu.reset();
	
	// set initial rpm
	flywheel->setTargetRPM(MEDIUM_RPM3);
}

void disabled()
{}

void competition_initialize()
{
	initialize();
}

void autonomous()
{
	// run selected auto program
	switch(selection)
	{	
		case CLOSE_AUTO:
			closeAuto = new CloseAuto(robot, teamColor);
			closeAuto->run();
			break;
			
		case FAR_AUTO:
			farAuto = new FarAuto(robot, teamColor);
			farAuto->run();
			break;
		
		case AUTO_SKILLS:
			autoSkills = new AutoSkills(robot, teamColor);
			autoSkills->run();
			break;
	}
}

void handleDriverMovement()
{
	drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY), 
							controller.getAnalog(ControllerAnalog::rightY));
}

void handleFlywheelControl()
{
	static int16_t minRPM = 3500;
	static int16_t maxRPM = 0;
	static bool logging = false;
	
	if(startLogging.isPressed() && !COMPITETION_MODE)
		logging = true;
		
	if(liftMode.isPressed() && logging && !COMPITETION_MODE)
	{
		logging = false;
		std::cout << "Min RPM: " << minRPM << std::endl;
		std::cout << "Max RPM: " << maxRPM << std::endl;
	}
	
	if(garboRange.isPressed())
		flywheel->setTargetRPM(GARBO_RPM);
	
	if(longRange.isPressed())
		flywheel->setTargetRPM(HIGH_RPM);
			
	if(mediumRange.isPressed())
		flywheel->setTargetRPM(MEDIUM_RPM);
	
	if(mediumRange2.isPressed())
		flywheel->setTargetRPM(MEDIUM_RPM2);
	
	if(mediumRange3.isPressed())
		flywheel->setTargetRPM(MEDIUM_RPM3);
	
	if(shortRange.isPressed())
		flywheel->setTargetRPM(LOW_RPM);
	
	flywheel->update();
	
	if(logging)
	{
		int16_t rpm = flywheel->getSpeed();
		if(rpm < minRPM)
		{
			minRPM = rpm;
 		}
 		
		if(rpm > maxRPM)
		{
			maxRPM = rpm;
 		}
	}
}

void handleIntakeControl()
{	
	static const uint16_t shutOffTime = 150; 
	static uint16_t time = 0;
	static bool shutOff = false;
	
	static uint16_t count = 0;
	static uint8_t previousColor = 0;
	
	if(rollerUp.isPressed() || rollerDown.isPressed())
	{
		manualIntakeControl = true;
		intake->on();
	}
	
	if(manualIntakeControl)
	{
		if(rollerUp.isPressed())
			intake->setDriveDirection(1);
		else if(rollerDown.isPressed())
			intake->setDriveDirection(-1);
		else
		{
			manualIntakeControl = false;
			intake->setDriveDirection(1);
			intake->off();
		}
	}
	else
	{
		// controls whether intake is in forward/reverse
		if(diskModeToggle.isPressed())
			diskMode = false;
		else
			diskMode = true;
		
		intake->setDriveDirection((diskMode ? 1 : -1));
		
		// turns intake on/off
		if(intakeOn.changedToPressed() && diskLift->getState() == DiskLift::LiftState::LOADING)
			if(!intake->isRunning())
				intake->on();
			else
				intake->off();
	}
	
	// turn off intake if lift move out of way to prevent jams and other terribleness
	if(diskLift->getState() == DiskLift::LiftState::READY_TO_FIRE)
		intake->off();
		
	if(diskLift->getDiskAmount() >= 2.5)
	{	
		diskLift->setDiskAmount(3);
		if(time >= shutOffTime)
		{
			time = 0;
			intake->off();
			shutOff = true;
		}
		
		if(!shutOff)
		{
			time += 10;
		}
		else
		{
				
		}
	}
	else
	{
		shutOff = false;
	}
	
	if(opticalSensor->getProximity() == 255)
	{				
		double hue = opticalSensor->getHue();
		
		if(teamColor == RED)
		{
				
		}
		else if(teamColor == BLUE)
		{
			
			if(intake->getSpeed() > 0)
			{
				if(previousColor == BLUE)
				{
					if(hue > 235 && hue < 360)
					{
						intake->off();
					}	
				}
			}
			else
			{
				// for reverse roller
				if(previousColor == RED)
				{
					if(hue > 220 && hue < 240)
					{
						intake->off();
					}	
				}
			}
		}
		if(hue > 10 && hue < 20)
		{
			previousColor = RED;
		}
		else if(hue > 220 && hue < 235)
		{
			previousColor = BLUE;
		}
	
		count++;
		if(count >= 100)
		{
			std::cout << "Optical Sensor Readings " << std::endl;
			std::cout << hue << std::endl << std::endl;
			count = 0;
		}
	}
	else
	{
		previousColor = 0;
	}
}

void handleLiftControl()
{
	// driver control lift stuff
	if(liftMode.changedToPressed())
	{
		if(diskLift->getState() == DiskLift::LiftState::LOADING)
			diskLift->readyToFire();
		else if(diskLift->getState() == DiskLift::LiftState::READY_TO_FIRE || 
				diskLift->getState() == DiskLift::LiftState::FIRING)
			diskLift->load();
	}
	
	if(fire.isPressed())
		diskLift->fire();
	
	
	// manual garbage
	/*if(manualMode.isPressed())
		diskLift->manual();*/
	
	// only works in manual mode
	if(diskLiftUp.isPressed())
		diskLift->move(1);
	else if(diskLiftDown.isPressed())
		diskLift->move(-1);		
	else
		diskLift->move(0);
	
	diskLift->update(flywheel);
}

void handleExpansionControl()
{
	if(expansionFire1.isPressed() && expansionFire2.isPressed() && 
	   expansionFire3.isPressed() && expansionFire4.isPressed() &&
	   expansionFire5.isPressed() && expansionFire6.isPressed())
	{
		if(diskLift->safeForExpansion())
		{
			expansion->fire();
		}
		else
		{
			diskLift->load();
		}
	}
}

void opcontrol()
{
	while(true)
	{
		handleDriverMovement();
		handleFlywheelControl();
		handleIntakeControl();
		handleLiftControl();
		handleExpansionControl();
		
		ControllerDisplayLayer::update(driveMotors, flywheel, intake);
		
		if(autoTest.changedToPressed() && !COMPITETION_MODE)
			autonomous();
		
		pros::delay(LOOP_DELAY);
	}
}
