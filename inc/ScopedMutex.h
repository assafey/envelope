/***********************************************************************
 * File name	: ScopedMutex.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Locks mutex inside the scope and release it at the end of the scope.
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/
#ifndef _SCOPED_MUTEX_H_
#define _SCOPED_MUTEX_H_

#include "Mutex.h"

class ScopedMutex
{
private:

	Mutex* m_MutexPtr;

public:

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	ScopedMutex(Mutex* mutex);

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	~ScopedMutex();

};

#endif
