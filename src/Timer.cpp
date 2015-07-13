/***********************************************************************
 * File name	: Timer.cpp
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Class for timer functionality
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/
#include "Timer.h"
#include <stdio.h>

void Timer::Sleep(unsigned int sec)
{
	MiliSleep(sec * 1000);
}

void Timer::MiliSleep(unsigned int msec)
{
	MicroSleep(msec * 1000ULL);
}

void Timer::MicroSleep(unsigned long long usec)
{
	NanoSleep(usec * 1000ULL);
}

void Timer::NanoSleep(unsigned long long nsec)
{
	struct timespec timeInfo;

	timeInfo.tv_sec  = nsec / NANO_IN_SEC;
	timeInfo.tv_nsec = nsec % NANO_IN_SEC;

	nanosleep(&timeInfo, NULL);
}

unsigned long long Timer::Time()
{
    time_t timeInfo = time(0);
    return timeInfo;
}

void Timer::Time(char* timeStr)
{
    time_t timeInfo = time(0);
    struct tm* now = localtime(&timeInfo);

    timeStr[0] = '\0';
    sprintf(timeStr, "%s", asctime(now));
}
