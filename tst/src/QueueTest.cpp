#include "QueueTest.h"

void QueueTest()
{
	Queue<int> q(3);
	int a = 4;

	Check.Start("Queue");

	Check.True(q.Put(&a), "put 1");

	a = 5;
	Check.True(q.Put(&a), "put 2");

	Check.True(q.Front(&a), "front");
	Check.Equals(a, 4, "front equals 4");
	Check.True(q.Back(&a), "back");
	Check.Equals(a, 5, "back equals 5");
	Check.Equals(q.Size(), 2U, "size equals 2");

	a = 6;
	Check.True(q.Put(&a), "put 3");

	Check.False(q.Put(&a), "put 4, overflow!");

	Check.True(q.Full(), "queue is full.");

	Check.True(q.Poll(&a), "poll 1");
	Check.Equals(a, 4, "poll 1 equals to 4");

	Check.True(q.Put(&a), "put 4");

	Check.True(q.Poll(&a), "poll 2");
	Check.Equals(a, 5, "poll 2 equals to 5");

	Check.True(q.Poll(&a), "poll 3");
	Check.Equals(a, 6, "poll 3 equals to 6");

	Check.True(q.Poll(&a), "poll 4");
	Check.Equals(a, 4, "poll 4 equals to 4");

	Check.True(q.Empty(), "queue empty");

	Check.End("Queue");
}
