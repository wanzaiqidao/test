#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int g_heapsize;

int left(int parent)
{
	int left = 0;
	if(parent <= g_heapsize/2)
	{
		left = parent*2;
	}
	return left;
}

int right(int parent)
{
	int right = 0;
	
}
void heap_max_balance(int array[], int index)
{
    	
}

