/***********************************************************************
 * File name	: Mutex.h
 * Date Created	: 12.7.15
 * Author		: Assaf Grimberg
 * Description	: Mutex envelope for pthread_mutex
 *
 * Change log:
 * [+] 2015-07-12, Assaf Grimberg: File Created.
 **********************************************************************/
#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_

#include <string.h>

#define HASH_MAP_KEY_LEN 20
#define HASH_MAP_DEFAULT_DEPTH 10

template<typename ElementType, int MapSize>
class HashMap
{
private:

	struct Element_t
	{
		int			Used;
		ElementType Data;
		char		Key[HASH_MAP_KEY_LEN];

		Element_t()
		{
			Reset();
		}

		void Set(const char* key, const ElementType* data)
		{
			Used = 1;
			Data = *data;
			strncpy(Key, key, HASH_MAP_KEY_LEN);
		}

		bool Compare(const char* key)
		{
			return strcmp(Key, key) == 0;
		}

		void Reset()
		{
			Used = 0;
			Key[0] = '\0';
		}
	};

	Element_t*			m_Elements[MapSize];
	const unsigned int 	m_Depth;

public:

	HashMap(unsigned int depth = HASH_MAP_DEFAULT_DEPTH) : m_Depth(depth)
	{
		for (int i = 0; i < MapSize; i++)
			m_Elements[i] = new Element_t[m_Depth];
	}

	bool Put(const char* key, const ElementType* element)
	{
		int h = Hash(key);

		for (int i = 0; i < m_Depth; i++)
		{
			if (m_Elements[h][i].Used == 0)
			{
				m_Elements[h][i].Set(key, element);
				return true;
			}
		}

		return false;
	}

	bool Get(const char* key, ElementType* element)
	{
		int h = Hash(key);

		for (int i = 0; i < m_Depth; i++)
		{
			if (m_Elements[h][i].Used == 1)
			{
				if (m_Elements[h][i].Compare(key))
				{
					*element = m_Elements[h][i].Data;
					m_Elements[h][i].Reset();
					return true;
				}
			}
		}

		return false;
	}

	bool Empty()
	{
		return Size() == 0;
	}

	bool Full()
	{
		return Size() == MapSize * m_Depth;
	}

	unsigned int Size()
	{
		int size = 0;

		for (int i = 0; i < MapSize; i++)
		{
			for (int j = 0; j < m_Depth; j++)
			{
				if (m_Elements[i][j].Used != 0)
					size++;
			}
		}

		return size;
	}

private:

	int Hash(const char* key)
	{
		//HASH: djb2 algorithm
		unsigned long hash = 5381;
		int c;

		while ((c = *key++) != '\0')
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		return hash % MapSize;
	}
};

#endif

