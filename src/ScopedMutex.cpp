/***********************************************************************
 * File name	: ScopedMutex.cpp
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Locks mutex inside the scope and release it at the end of the scope.
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/

#include "ScopedMutex.h"

ScopedMutex::ScopedMutex(Mutex& mutex) :
	m_MutexPtr(&mutex)
{
	m_MutexPtr->Lock();
}

ScopedMutex::~ScopedMutex()
{
	m_MutexPtr->Unlock();
}
