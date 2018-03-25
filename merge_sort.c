#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void merge(int src[], int tmp[], int start, int mid, int end)
{
	int i, j, k;
	assert(NULL != src);
	assert(NULL != tmp);

	i = start;
	j = mid + 1;
	k = start;

	while((i<=mid) && (j<=end))
	{
		if(src[i] <= src[j])
		{
			tmp[k++] = src[i++];
		}
		else
		{
			tmp[k++] = src[j++];
		}
	}

	while(i <= mid)
	{
		tmp[k++] = src[i++];
	}
	while(j <= end)
	{
		tmp[k++] = src[j++];
	}

	memcpy(src+start, tmp+start, sizeof(int)*(end-start+1));
	return;
}

void merge_sort(int src[], int tmp[], int start, int end)
{
	int mid;
	assert(NULL != src);
	assert(NULL != tmp);

	mid = (start+end)/2;
	if(start < end)
	{
		merge_sort(src, tmp, start, mid);
		merge_sort(src, tmp, mid+1, end);
		merge(src, tmp, start, mid, end);
	}
	else
	{
		return;
	}
}

int main(int argc, char *argv[])
{
	int *tmp, *src, index;
	assert(argc > 1);

	src = malloc(sizeof(int) * (argc-1));
	tmp = malloc(sizeof(int) * (argc-1));
	if((NULL==tmp) || (NULL == src))
	{
		return -1;
	}

	for(index=0; index<argc-1; index++)
	{
		src[index] = atoi(argv[index+1]);
		printf("%d  ", src[index]);
	}
	printf("\n");

	merge_sort(src, tmp, 0, argc-2);
	printf("the result is:\n");
	for(index=0; index<argc-1; index++)
	{
		printf("%d  ", src[index]);
	}
	printf("\n");
	return 0;
}
