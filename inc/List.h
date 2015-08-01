/***********************************************************************
 * File name	: List.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: List class
 *
 * Change log:
 * [+] 2015-08-01, Assaf Grimberg: File Created.
 **********************************************************************/
#ifndef _LIST_H_
#define _LIST_H_

#define LIST_DEFAULT_SIZE 10

template<typename ElementType>
class List
{
private:

	struct Element_t
	{
		int 			Used;
		ElementType		Element;

		Element_t()
		{
			Used = 0;
		}
	};

	unsigned int 		m_Count;
	const unsigned int 	m_Size;

	Element_t*			m_TheList;

public:

	List(unsigned int size = LIST_DEFAULT_SIZE) : m_Count(0), m_Size(size)
	{
		m_TheList = new Element_t[m_Size];
	}

	int Add(const ElementType* element)
	{
		if (Full())
			return -1;

		for (int index = 0; index < m_Size; index++)
		{
			if (!m_TheList[index].Used)
			{
				m_TheList[index].Used = 1;
				m_TheList[index].Element = *element;
				m_Count++;
				return index;
			}
		}

		return -1;
	}

	bool Remove(unsigned int index)
	{
		if (Empty())
			return false;

		if (index >= m_Size)
			return false;

		m_TheList[index].Used = 0;
		m_Count--;

		return true;
	}

	bool Get(unsigned int index, ElementType& outElement)
	{
		if (Empty())
			return false;

		if (index >= m_Size)
			return false;

		outElement = m_TheList[index].Element;

		return true;
	}

	bool Empty()const
	{
		return m_Count == 0;
	}

	bool Full()const
	{
		return m_Count == m_Size;
	}

	unsigned int Size()const
	{
		return m_Size;
	}

	unsigned int Count()const
	{
		return m_Count;
	}
};

#endif
