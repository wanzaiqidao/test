#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int g_heapsize;

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

void heap_sort(int array[], int size)
{
    int index;
    assert(NULL != array);

    g_heapsize = size;
    heap_build(array);
    for(index=size; index>1; index--)
    {
        heap_exchange(array, index, 1);
        g_heapsize--;
        heap_max_ify(array, 1);
    }

    return;
}

int main(int argc, char *argv[])
{
    int index;
    int *array;
    assert(1 < argc);

    array = malloc(sizeof(int) * argc);
    if(NULL == array)
    {
        return 0;
    }
    array[0] = 0;
    for(index=1; index<argc; index++)
    {
        array[index] = atoi(argv[index]);
        printf("%d  ", array[index]);
    }
    printf("\n");

    heap_sort(array, argc-1);
    printf("the result is:\n");
    for(index=1; index<argc; index++)
    {
        printf("%d  ", array[index]);
    }
    printf("\n");
    
    return 0;
}

