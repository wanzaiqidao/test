#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int g_heapsize;

int heap_parent(int child)
{
    int parent;
    assert(child<=g_heapsize); 

    parent = child/2;
    return parent;
}

int heap_left(int parent)
{
	int left = 0;
	if(parent <= g_heapsize/2)
	{
		left = parent*2;
	}
	return left;
}

int heap_right(int parent)
{
	int right = 0;
    if(parent <= g_heapsize/2)
    {
        right = parent*2 + 1;
        if(right>g_heapsize)
        {
            right = 0;
        }
    }
	return right;
}

int heap_maximum(int array[])
{
    assert(NULL != array);
    return array[1];
}

void heap_exchange(int array[], int i, int j)
{
    int tmp;
    assert(NULL != array);

    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;

    return;
}

void heap_max_ify(int array[], int index)
{
    int left, right, largest;
    assert(NULL != array);
    if(index > g_heapsize/2)
    {
        return;
    }
    
    left = heap_left(index);
    right = heap_right(index);

    largest = index;
    if(array[index] < array[left])
    {
        largest = left;
    }
    if(array[largest] < array[right])
    {
        largest = right;
    }

    if(largest != index)
    {
        heap_exchange(array, index, largest);
        heap_max_ify(array, largest);
    }    
    return;    	
}

void heap_build(int array[])
{
    int index;
    assert(NULL != array);

    for(index=g_heapsize/2; index>0; index--)
    {
        heap_max_ify(array, index);
    }
    return;
}

int heap_extract_max(int array[])
{
    int max, parent;
    assert(NULL != array);

    max = array[1];
    array[1] = array[g_heapsize];
    g_heapsize--;
    heap_max_ify(array, 1);
    
    return max;
}

void heap_increase_key(int array[], int index, int key)
{
    int parent;
    assert(NULL != array);
    assert(key >= array[index]);
    
    array[index] = key;
    parent = heap_parent(index);
    while((index>1) && (array[parent]<array[index])
    {
        heap_exchange(array, index, parent);
        index = parent;
        parent = heap_parent(index);
    }
    
    return;
}
void heap_insert(int array[], int key)
{
    int parent;
    assert(NULL != array);

    g_heapsize++;
    array[g_heapsize] = 0;
    heap_increase_key(array, g_heapsize, key);
    return;
}