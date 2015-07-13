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
	Mutex				m_Mutex;

public:

	Queue(unsigned int depth = QUEUE_DEFAULT_DEPTH) : m_Depth(depth)
	{
		m_Elements = new ElementType[m_Depth];
		m_Top = m_Bottom = 0;
	}

	~Queue()
	{
		if (m_Elements)
			delete[] m_Elements;
	}

	bool Front(ElementType* element)
	{
		ScopedMutex scope(&m_Mutex);

		if (Empty())
			return false;

		*element = m_Elements[m_Top];

		return true;
	}

	bool Back(ElementType* element)
	{
		ScopedMutex scope(&m_Mutex);

		if (Empty())
			return false;

		*element = m_Elements[m_Bottom];

		return true;
	}

	bool Put(const ElementType* element)
	{
		ScopedMutex scope(&m_Mutex);

		int top = m_Top;

		top++;
		if (top >= m_Depth)
			return false;

		m_Top = top;
		m_Elements[m_Top] = *element;

		return true;
	}

	bool Poll(ElementType* element)
	{
		ScopedMutex scope(&m_Mutex);

		if (Empty())
			return false;

		if (!Peek(element))
			return false;

		m_Top--;

		return true;
	}

	bool Empty()
	{
		ScopedMutex scope(&m_Mutex);

		return m_Top == m_Bottom;
	}

	unsigned int Size()
	{
		ScopedMutex scope(&m_Mutex);

		return m_Top - m_Bottom + 1;
	}
};

#endif
