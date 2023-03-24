#include "AutoProgram.h"

#define LOOP_DELAY 10
#define CYCLE_TIME 1000

AutoProgram::AutoProgram(Robot& robot)
{
	this->robot = &robot;
	left = new MotorGroup{ robot.driveMotors[0], robot.driveMotors[1]};
	right = new MotorGroup{ robot.driveMotors[2], robot.driveMotors[3]};
	
	estimatedTime = 0.0;
}

AutoProgram::~AutoProgram()
{
	delete left;
	delete right;
}

void AutoProgram::addTask(AutoTask* task, uint64_t time)
{
	task->setTime(time);
	task->setRobot(robot);
	tasks.push_back(task);
	estimatedTime += time;
}

void AutoProgram::run()
{
	bool running = true;
	uint64_t time = 0;
	uint16_t taskIndex = 0;
	
	Timer timer;
	
	QTime current;
	QTime last = timer.millis();
	QTime delta;
	
	std::cout << "Starting Autonomous Program" << std::endl;
	std::cout << "Estimated Completion Time is " << getEstimatedTime() << " Seconds" << std::endl;
	
	while(running)
	{
		if(taskIndex < tasks.size())
		{
			AutoTask* task = tasks[taskIndex];
			if(time >= task->getTime())
			{
				task->run();
				runningTasks.push_back(task);
				
				// handles zero delay tasks
				// ensures that any tasks that must happen at the same time have no delay
				for(uint16_t i = taskIndex + 1; i < tasks.size(); i++)
				{
					AutoTask* zeroDelayTask = tasks[i];
					if(zeroDelayTask->getTime() == 0)
					{
						// run any zero delay tasks
						zeroDelayTask->run();
						runningTasks.push_back(zeroDelayTask);
						
						// zero delay tasks are accounted for
						taskIndex++;
					}
					else
						break;
				}
				
				// reset timer and increment task index for the specific task 
				time = 0;
				taskIndex++;
			}
		}
		
		current = timer.millis();
		delta = current - last;
		for(AutoTask* task : runningTasks)
		{
			if(!task->isDone())
			{
				task->setDelta(delta);
				task->update();
				
				if(task->isDone())
					task->exit();
			}
		}
		
		robot->flywheel->update();
		robot->diskLift->update(robot->flywheel);
		
		bool done = true;
		for(AutoTask* task : tasks)
			if(!task->isDone())
			{
				done = false;
				break;
			}
		
		if(done)
			running = false;
		
		pros::delay(LOOP_DELAY);
		time += LOOP_DELAY;	
	
		last = current;
	}
	
	for(AutoTask* task : tasks)
		task->reset();
}

double AutoProgram::getEstimatedTime()
{
	return (estimatedTime / 1000);
}

void AutoProgram::fireDisks(uint8_t amount)
{
	for(uint8_t i = 0; i < amount; i++)
	{
		robot->diskLift->fire();
		
		if(i > 1)
			pros::delay(CYCLE_TIME);
	}
	
	robot->diskLift->load();
}
