/***********************************************************************
 * File name	: Timer.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Class for timer functionality
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <unistd.h>
#include <string.h>

#define NANO_IN_SEC 1000000000ULL

class Timer
{
public:

	static void Sleep(unsigned int sec);

	static void MiliSleep(unsigned int msec);

	static void MicroSleep(unsigned long long usec);

	static void NanoSleep(unsigned long long nsec);

	static unsigned long long Time();

	static void Time(char* timeStr);
};

#endif
