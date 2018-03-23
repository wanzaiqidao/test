#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void quick_sort(int array[], int left, int right)
{
	int i, j, key;
	
	assert(NULL != array);
	if(left >= right)
	{
		return;
	}

	key = array[left];
	i = left;
	j = right;

	while(i < j)
	{
		while((array[j]>=key) && (j>i))
		{
			j--;
		}
		array[i] = array[j];

		while((array[i]<=key) && (j>i))
		{
			i++;
		}
		array[j] = array[i];
	}

	array[i] = key;
	quick_sort(array, left, i-1);
	quick_sort(array, i+1, right);

	return;
}

int main(int argc, char *argv[])
{
	int i;
	int *ptr;
	assert(argc > 1);

	ptr = malloc(sizeof(int) * (argc-1));

	for(i=1; i<argc; i++)
	{
		ptr[i-1] = atoi(argv[i]);
		printf("%d  ", ptr[i-1]);
	}
	printf("\n");

	quick_sort(ptr, 0, argc-2);

	printf("the result is:\n");
	for(i=0; i<argc-1; i++)
	{
		printf("%d  ", ptr[i]);
	}
	printf("\n");

	return 0;
}
