/***********************************************************************
 * File name	: Queue.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Queue class
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "ScopedMutex.h"
#include "Mutex.h"

#define QUEUE_DEFAULT_DEPTH 10

template<typename ElementType>
class Queue
{
private:

	ElementType* 		m_Elements;
	const unsigned int 	m_Depth;
	int 				m_Top;
	int 				m_Bottom;
	unsigned int 		m_Count;
	Mutex				m_Mutex;

public:

	Queue(unsigned int depth = QUEUE_DEFAULT_DEPTH) :
		m_Depth(depth), m_Top(-1), m_Bottom(-1), m_Count(0)
	{
		m_Elements = new ElementType[m_Depth];
	}

	~Queue()
	{
		if (m_Elements)
			delete[] m_Elements;
	}

	bool Front(ElementType* element)
	{
		ScopedMutex scope(m_Mutex);

		if (Empty())
			return false;

		*element = m_Elements[m_Top];

		return true;
	}

	bool Back(ElementType* element)
	{
		ScopedMutex scope(m_Mutex);

		if (Empty())
			return false;

		*element = m_Elements[m_Bottom];

		return true;
	}

	bool Put(const ElementType* element)
	{
		ScopedMutex scope(m_Mutex);

		if (Full())
			return false;

		if (m_Top < 0)
			m_Top = 0;

		m_Bottom = (m_Bottom + 1) % m_Depth;
		m_Count++;

		m_Elements[m_Bottom] = *element;

		return true;
	}

	bool Poll(ElementType* element)
	{
		ScopedMutex scope(m_Mutex);

		if (!Front(element))
			return false;

		m_Top = (m_Top + 1) % m_Depth;
		m_Count--;

		return true;
	}

	void Clear()
	{
		ScopedMutex scope(m_Mutex);

		m_Count = 0;
		m_Top = -1;
		m_Bottom = -1;
	}

	bool Empty()
	{
		ScopedMutex scope(m_Mutex);

		return Size() == 0;
	}

	bool Full()
	{
		ScopedMutex scope(m_Mutex);

		return Size() == m_Depth;
	}

	unsigned int Size()
	{
		ScopedMutex scope(m_Mutex);

		return m_Count;
	}
};

#endif
