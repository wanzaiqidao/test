#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void heap_min_ify(int array[], int index)
{
    int left, right, lowest;
    assert(NULL != array);
    if(index > g_heapsize/2)
    {
        return;
    }
    
    left = heap_left(index);
    right = heap_right(index);

    lowest = index;
    if(array[index] > array[left])
    {
        lowest = left;
    }
    if(array[lowest] > array[right])
    {
        lowest = right;
    }

    if(lowest != index)
    {
        heap_exchange(array, index, lowest);
        heap_min_ify(array, lowest);
    }    
    return;    	
}

void heap_build(int array[])
{
    int index;
    assert(NULL != array);

    for(index=g_heapsize/2; index>0; index--)
    {
        heap_min_ify(array, index);
    }
    return;
}

void find_top(int array[], FILE *fp)
{
    int next, index, tmp;
    char buf[256], *ptr;
    assert(NULL != array);
    assert(NULL != fp);

    index = 1;
    while((index<=g_heapsize) && (NULL != (ptr=fgets(buf, sizeof(buf), fp))))
    {
        array[index] = atoi(buf);
        index++;
    }
    assert(NULL != ptr);
    heap_build(array);

    while(NULL != fgets(buf, sizeof(buf), fp))
    {
        tmp = atoi(buf);
        if(tmp > array[1])
        {
            array[1] = tmp;
            heap_min_ify(array, 1);
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    int index, size;
    FILE *in, *out;
    int *array;
    char buf[20];
    assert(4 == argc);

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if((NULL == in) || (NULL == out))
    {
        return -1;   
    }

    g_heapsize = atoi(argv[3]);
    size = sizeof(int)*(g_heapsize+1);
    array = malloc(size);
    if(NULL != array)
    {
        return -1;
    }
    memset(array, 0, size);
    find_top(array, in);

    for(index=1; index<=g_heapsize; index++)
    {
        snprintf(buf, sizeof(buf), "%d", array[index]);
        fputs(buf, out);
        fputs("\n", out);
    }

    fclose(in);
    fclose(out);
    free(array);
    
}

