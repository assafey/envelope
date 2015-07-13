#include <stdio.h>
#include <unistd.h>
#include "Thread.h"
#include "Timer.h"
#include "Stack.h"
#include "HashMap.h"

void ThreadTest(void* obj, void* param)
{
	/*int count = 500000000;
	while (count > 0) {
		count--;
	}*/

	Timer::MiliSleep(500);

	printf("In thread func.\n");

	Timer::MiliSleep(500);

	/*count = 500000000;
	while (count > 0) {
		count--;
	}*/

	printf("Thread finished.\n");
}

int main()
{
	HashMap<int, 10> map;

	int val = 10;
	map.Put("assaf", &val);
	val = 100;
	map.Put("hilla", &val);
	val = 1000;
	map.Put("rachel", &val);

	printf("map.Size=%u (should be 3)\n", map.Size());
	map.Get("hilla", &val);
	printf("map.Get=%d (should be 100) size=%u\n", val, map.Size());
	map.Get("rachel", &val);
	printf("map.Get=%d (should be 1000) size=%u\n", val, map.Size());
	map.Get("assaf", &val);
	printf("map.Get=%d (should be 10) size=%u\n", val, map.Size());

	if (map.Empty())
		printf("map.Empty :)\n");
	else
		printf("map.Empty :( not empty...\n");

	Stack<int> s;
	Thread thread("tTest");
	
	int a = 'a', b = 'b', c = 'c';

	s.Push(&a);
	s.Push(&b);
	s.Push(&c);

	s.Peek(&a);
	printf("test s.Peek=%c (should be 'c')\n", (char)a);
	printf("test s.Size=%u (should be 3)\n", s.Size());

	s.Pop(&a);
	printf("test s.Pop=%c (should be 'c')\n", (char)a);
	printf("test s.Size=%u (should be 2)\n", s.Size());

	s.Pop(&a); // b
	s.Pop(&a); // a
	printf("test s.Pop=%c (should be 'a')\n", (char)a);
	printf("test s.Size=%u (should be 0)\n", s.Size());

	if (s.Empty())
		printf("s.Empty :)\n");
	else
		printf("s.Empty :( not empty...\n");

	if (!thread.Start(ThreadTest, NULL))
	{
		printf("Test failed.\n");
	}
	else
	{
		thread.Wait();

		//thread.Stop();
		//Timer::Sleep(4);
	}
	
	Timer::Sleep(2);

	char timeStr[30];
	printf("time: %llu\n", Timer::Time());

	Timer::Time(timeStr);
	printf("time %s\n", timeStr);

	printf("Finished.\n");

	return 0;
}
