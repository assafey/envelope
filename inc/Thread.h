/***********************************************************************
 * File name	: Thread.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Thread wrapper for pthread
 * 
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/ 
#ifndef _THREAD_H_
#define _THREAD_H_
 
#include <pthread.h>
#include <string.h>

#include "ScopedMutex.h"
#include "Mutex.h"
 
 typedef void(*ThreadFunc)(void*,void*);
 static const int DEFAULT_STACK_SIZE = 2 * 1024 * 1024; // 2MB
 static const int DEFAULT_THREAD_PRIORITY = 150;
 
 class Thread
 {
private:

	enum { NAME_LEN = 20 };
		
	pthread_t 		m_TheThread;
	pthread_attr_t	m_Attr;
	ThreadFunc		m_TheFunc;
	void* 			m_Param;
	void* 			m_Object;
	char 			m_Name[NAME_LEN];
	Mutex			m_Mutex;
	
public:
	
	/**************************************************
	 * Description:
	 *
	 **************************************************/
	Thread
	(
		const char* tName = NULL,					// In: the thread name
		int tStackSize = DEFAULT_STACK_SIZE, 		// In: optional - stack size 
		int tPriority = DEFAULT_THREAD_PRIORITY		// In: optional - thread priority
	);
	
	/**************************************************
	 * Description:
	 *
	 **************************************************/
	~Thread();
	
	/**************************************************
	 * Description:
	 *
	 **************************************************/
	bool Start
	(
		ThreadFunc tFunc, 		// In: the thread function
		void* obj, 				// In: the operating object of the thread
		void* param = NULL		// In: optional - parameter to thread function
	);
	
	/**************************************************
	 * Description:
	 *
	 **************************************************/
	bool Wait();
	
	/**************************************************
	 * Description:
	 * Flags the thread to cancel itself.
	 * WARNING: this won't stops the thread, just signals
	 * it to cancel (if it can).
	 **************************************************/
	bool Stop();

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	const char* Name();
	 
private:

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	static void* Runner(void* self);	

	/**************************************************
	 * Description:
	 *
	 **************************************************/
	void Run();

 };
 
 #endif
