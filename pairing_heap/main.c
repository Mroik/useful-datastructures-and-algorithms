#include <stdio.h>

#include "pairing_heap.h"

int main()
{
	node* a = make_node(6);
	a = insert(a, 1);
	a = insert(a, 3);
	a = insert(a, 5);
	a = insert(a, 2);
	for(int x = 0; x < 5; x++)
	{
		printf("%d\n", top(a));
		a = pop(a);
	}
	printf("Pointer at last should have address 0: %d\n", a);
}
