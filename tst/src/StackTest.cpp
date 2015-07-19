#include <stdio.h>
#include "StackTest.h"

void StackTest()
{
	Stack<int> s(3);
	int a = 'a', b = 'b', c = 'c';

	Check.Start("Stack");

	s.Push(&a);
	Check.Equals(s.Size(), 1U, "size after push 1");

	Check.False(s.Empty(), "stack not empty");

	s.Push(&b);
	Check.Equals(s.Size(), 2U, "size after push 2");

	s.Push(&c);
	Check.Equals(s.Size(), 3U, "size after push 3");

	Check.True(s.Full(), "stack full");

	s.Peek(&a);
	Check.Equals(a, (int)'c', "peek");
	Check.Equals(s.Size(), 3U, "size same after peek");

	s.Pop(&a); // c
	Check.Equals(a, (int)'c', "pop 1");
	Check.Equals(s.Size(), 2U, "size after pop 1");

	s.Pop(&a); // b
	Check.Equals(a, (int)'b', "pop 2");
	Check.Equals(s.Size(), 1U, "size after pop 2");

	s.Pop(&a); // a
	Check.Equals(a, (int)'a', "pop 3");
	Check.Zero(s.Size(), "size after pop 3");

	Check.True(s.Empty(), "stack is empty");

	Check.End("Stack");
}
