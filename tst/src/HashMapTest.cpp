#include "HashMapTest.h"

void HashMapTest()
{
	HashMap<int, 5> map;

	Check.Start("HashMap");

	int val = 10;
	map.Put("assaf", &val);
	Check.Equals(map.Size(), 1U, "map size after put 1");

	val = 100;
	map.Put("hilla", &val);
	Check.Equals(map.Size(), 2U, "map size after put 2");

	val = 1000;
	map.Put("rachel", &val);
	Check.Equals(map.Size(), 3U, "map size after put 3");

	map.Get("hilla", &val);
	Check.Equals(val, 100, "get 1 value");

	map.Get("rachel", &val);
	Check.Equals(val, 1000, "get 2 value");

	map.Get("assaf", &val);
	Check.Equals(val, 10, "get 3 value");

	map.Clear();
	Check.True(map.Empty(), "map is empty after clear");

	val = 100;
	map.Put("hilla", &val);
	Check.Equals(map.Size(), 1U, "map size after put 4");

	val = 1000;
	map.Put("rachel", &val);
	Check.Equals(map.Size(), 2U, "map size after put 5");

	unsigned int numOfKeys = 0;
	char keys[3][HASH_MAP_KEY_LEN];
	map.Keys<3>(keys, numOfKeys);
	Check.Equals(numOfKeys, 2U, "2 keys!");

	for (int i = 0; i < numOfKeys; i++) {
		const char* key = keys[i];
		Check.True(map.Remove(key), "key removed");
	}

	Check.True(map.Empty(), "map is empty after remove");

	Check.End("HashMap");
}
