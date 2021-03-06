#include <stdio.h>
#include "ThreadTest.h"
#include "Timer.h"

void Task(void* obj, void* param)
{
	Timer::MiliSleep(500);

	Check.Pass("In thread func.");

	Timer::MiliSleep(500);

	Check.Pass("Thread finished.");
}

void ThreadTest()
{
	Thread thread("tTest");

	Check.Start("Thread");

	bool started = thread.Start(Task, NULL);
	Check.True(started, "thread started");
	
	if (started)
	{
		thread.Wait();
	}
	
	Check.Pass("Finished.");

	Check.End("Thread");
}
