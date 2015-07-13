#include "HashMapTest.h"

void HashMapTest()
{
	HashMap<int, 5> map;

	Check.Subject("===== HashMap Test Start =====");

	int val = 10;
	map.Put("assaf", &val);
	Check.Equals(map.Size(), 1U, "map size after put 1");

	val = 100;
	map.Put("hilla", &val);
	Check.Equals(map.Size(), 2U, "map size after put 2");

	val = 1000;
	map.Put("rachel", &val);
	Check.Equals(map.Size(), 3U, "map size after put 3");

	bool peeked = map.Peek("hilla", &val);
	Check.True(peeked, "peek");
	Check.Equals(val, 100, "peek value");
	Check.Equals(map.Size(), 3U, "size remain after peek");

	map.Get("hilla", &val);
	Check.Equals(val, 100, "get 1 value");
	Check.Equals(map.Size(), 2U, "size after get 1");

	map.Get("rachel", &val);
	Check.Equals(val, 1000, "get 2 value");
	Check.Equals(map.Size(), 1U, "size after get 2");

	map.Get("assaf", &val);
	Check.Equals(val, 10, "get 3 value");
	Check.Zero(map.Size(), "size after get 3");

	Check.True(map.Empty(), "map is empty");

	Check.Subject("===== HashMap Test End =====\n");
}
