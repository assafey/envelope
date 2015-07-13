/***********************************************************************
 * File name	: Stack.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Stack class
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/
#ifndef _STACK_H_
#define _STACK_H_

#include "Mutex.h"
#include "ScopedMutex.h"

#define STACK_DEFAULT_DEPTH 10

template<typename ElementType>
class Stack
{
	private:

	ElementType* 		m_Elements;
	const unsigned int 	m_Depth;
	int 				m_Top;
	Mutex				m_Mutex;

public:

	Stack(unsigned int depth = STACK_DEFAULT_DEPTH) : m_Depth(depth)
	{
		m_Elements = new ElementType[m_Depth];
		m_Top = -1;
	}

	~Stack()
	{
		if (m_Elements)
			delete[] m_Elements;
	}

	bool Peek(ElementType* element)
	{
		ScopedMutex scope(&m_Mutex);

		if (Empty())
			return false;

		*element = m_Elements[m_Top];

		return true;
	}

	bool Push(const ElementType* element)
	{
		ScopedMutex scope(&m_Mutex);

		if (Full())
			return false;

		m_Top++;
		m_Elements[m_Top] = *element;

		return true;
	}

	bool Pop(ElementType* element)
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

		return m_Top < 0;
	}

	bool Full()
	{
		if (m_Top + 1 == m_Depth)
			return true;
		else
			return false;
	}

	unsigned int Size()
	{
		ScopedMutex scope(&m_Mutex);

		return m_Top + 1;
	}
};

#endif
