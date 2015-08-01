/***********************************************************************
 * File name	: Thread.cpp
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Thread wrapper for pthread
 * 
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/

#include "Thread.h"
#include <stdio.h>

/***********************************************************************
 * Public methods
 **********************************************************************/

Thread::Thread
(
	const char* tName,		// In: the thread name 	
	int tStackSize, 		// In: optional - stack size 
	int tPriority			// In: optional - thread priority
)
{	
	struct sched_param sched;
	sched.sched_priority = tPriority;
	
	m_Object = NULL;
	m_Param = NULL;
	m_TheFunc = NULL;
	m_TheThread = 0;
	m_Name[0] = '\0';

	pthread_attr_init(&m_Attr);
	pthread_attr_setstacksize(&m_Attr, tStackSize);
	pthread_attr_setschedparam(&m_Attr, &sched);

	if (tName)
		strncpy(m_Name, tName, NAME_LEN);
}
	
Thread::~Thread()
{
	Stop();

	pthread_detach(m_TheThread);
}
	
bool Thread::Start
(
	ThreadFunc tFunc, 		// In: the thread function
	void* obj, 				// In: the operating object of the thread
	void* param				// In: optional - parameter to thread function
)
{
	ScopedMutex scope(m_Mutex);

	m_TheFunc = tFunc;
	m_Param = param;
	m_Object = obj;
	
	if (pthread_create(&m_TheThread, &m_Attr, Runner, this) != 0)
		return false;

	return true;
}
	
bool Thread::Wait()
{
	if (pthread_join(m_TheThread, NULL) != 0)
		return false;
	
	return true;
}
	
bool Thread::Stop()
{
	if (pthread_cancel(m_TheThread) != 0)
		return false;

	return true;
}

const char* Thread::Name()
{
	return m_Name;
}

/***********************************************************************
 * Private methods
 **********************************************************************/
	
void* Thread::Runner(void* self)
{
	Thread* pSelf = (Thread*)self;

	pSelf->Run();

	return NULL;
}

void Thread::Run()
{
	if (strlen(m_Name) != 0)
		pthread_setname_np(m_Name);

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0)
		printf("failed to set cancel state.\n");

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	m_TheFunc(m_Object, m_Param);
}

