/***********************************************************************
 * File name	: Mutex.cpp
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Mutex envelope for pthread_mutex
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/

#include "Mutex.h"

Mutex::Mutex()
{
	pthread_mutexattr_init(&m_Attr);
	pthread_mutexattr_settype(&m_Attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_TheMutex, &m_Attr);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_TheMutex);
}

bool Mutex::Lock()
{
	if (pthread_mutex_lock(&m_TheMutex) != 0)
		return false;

	return true;
}

bool Mutex::Unlock()
{
	if (pthread_mutex_unlock(&m_TheMutex) != 0)
		return false;

	return true;
}

bool Mutex::TryLock()
{
	if (pthread_mutex_trylock(&m_TheMutex) != 0)
		return false;

	return true;
}
