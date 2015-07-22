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
	unsigned int 		m_Count;

public:

	HashMap(unsigned int depth = HASH_MAP_DEFAULT_DEPTH) :
		m_Depth(depth), m_Count(0)
	{
		for (int i = 0; i < MapSize; i++)
			m_Elements[i] = new Element_t[m_Depth];
	}

	~HashMap()
	{
		for (int i = 0; i < MapSize; i++)
			delete[] m_Elements[i];
	}

	bool Put(const char* key, const ElementType* element)
	{
		if (Exists(key))
			return false;

		int h = Hash(key);

		for (int i = 0; i < m_Depth; i++)
		{
			if (!m_Elements[h][i].Used)
			{
				m_Elements[h][i].Set(key, element);
				m_Count++;
				return true;
			}
		}

		return false;
	}

	bool Get(const char* key, ElementType* element)
	{
		int h = Hash(key);

		int index = Find(h, key);
		if (index >= 0)
		{
			*element = m_Elements[h][index].Data;
			return true;
		}

		return false;
	}

	bool Remove(const char* key)
	{
		int h = Hash(key);

		int index = Find(h, key);
		if (index >= 0)
		{
			m_Elements[h][index].Reset();
			m_Count--;
			return true;
		}

		return false;
	}

	template<int MaxNumOfKeys>
	void Keys(char keys[MaxNumOfKeys][HASH_MAP_KEY_LEN], unsigned int& outNumOfKeys)
	{
		int keyIdx = 0;

		for (int row = 0; row < MapSize; row++)
		{
			for (int col = 0; col < m_Depth; col++)
			{
				if (m_Elements[row][col].Used)
				{
					strncpy(keys[keyIdx], m_Elements[row][col].Key, HASH_MAP_KEY_LEN);
					keyIdx++;
					if (keyIdx >= MaxNumOfKeys)
						break;
				}
			}
		}

		outNumOfKeys = keyIdx;
	}

	void Clear()
	{
		for (int row = 0; row < MapSize; row++)
		{
			for (int col = 0; col < m_Depth; col++)
			{
				m_Elements[row][col].Reset();
			}
		}

		m_Count = 0;
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
		return m_Count;
	}

	bool Exists(const char* key)
	{
		int h = Hash(key);

		return Find(h, key) >= 0;
	}

private:

	int Find(int h, const char* key)
	{
		int index = -1;

		for (int i = 0; i < m_Depth; i++)
		{
			if (m_Elements[h][i].Used)
			{
				if (m_Elements[h][i].Compare(key))
				{
					index = i;
					break;
				}
			}
		}

		return index;
	}

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

