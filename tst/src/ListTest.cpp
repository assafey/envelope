#include "ListTest.h"

void ListTest()
{
	List<int> list(3);

	Check.Start("List");

	Check.True(list.Empty(), "list is empty");

	int a = 5;
	int index = list.Add(&a);
	Check.NotNegative(index, "Add to list 1");

	a = 7;
	index = list.Add(&a);
	Check.NotNegative(index, "Add to list 2");

	a = 9;
	index = list.Add(&a);
	Check.NotNegative(index, "Add to list 3");

	Check.True(list.Full(), "list is full");

	a = 0;
	index = list.Add(&a);
	Check.Negative(index, "Add to list 4");

	char msg[15];

	for (unsigned int i = 0; i < list.Size(); i++)
	{
		msg[0] = '\0';

		sprintf(msg, "Remove index %u from list", i);
		Check.True(list.Remove(i), msg);
	}

	Check.True(list.Empty(), "list is empty again");

	Check.End("List");
}
