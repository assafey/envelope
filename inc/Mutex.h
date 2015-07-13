/***********************************************************************
 * File name	: Mutex.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Mutex envelope for pthread_mutex
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/
#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

class Mutex
{
private:

	pthread_mutex_t 	m_TheMutex;
	pthread_mutexattr_t	m_Attr;

public:

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	Mutex();

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	~Mutex();

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	bool Lock();

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	bool Unlock();

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	bool TryLock();

};

#endif
