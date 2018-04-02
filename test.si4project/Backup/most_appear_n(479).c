#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct tagPhoneNumber
{
    struct tagPhoneNumber *next;
    char Number[12];
    int  Count;
}PhoneNumber;

typedef int (*pfKey)(char *key);
typedef int (*pfCmp)(char *key, PhoneNumber *node);
typedef struct taghash
{
    pfKey HashKey;
    pfCmp HashCmp;
    PhoneNumber *Bucket[1024];
}hash_t;
int hash_key(char *key);
int hash_cmp(char *key, PhoneNumber *node);
hash_t g_HashBucket = {hash_key, hash_cmp, {NULL}};

int g_heapsize = 0;
int g_heapindex = 1;

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

void heap_exchange(PhoneNumber *array[], int i, int j)
{
    PhoneNumber *tmp;
    assert(NULL != array);

    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;

    return;
}

void heap_min_ify(PhoneNumber *array[], int index)
{
    int left, right, lowest;
    assert(NULL != array);
    if((index > g_heapsize/2) || (index==0))
    {
        return;
    }
    
    left = heap_left(index);
    right = heap_right(index);

    lowest = index;
    if((array[lowest]->Count > array[left]->Count) && (left != 0))
    {
        lowest = left;
    }
    if((array[lowest]->Count > array[right]->Count) && (right != 0))
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

void heap_build(PhoneNumber *array[])
{
    int index;
    assert(NULL != array);

    for(index=g_heapsize/2; index>0; index--)
    {
        heap_min_ify(array, index);
    }
    return;
}

void find_top(PhoneNumber *array[], hash_t *hash)
{
    int next, key;
    PhoneNumber *head, *tmp;
    assert(NULL != array);
    assert(NULL != hash);

    if(g_heapindex <= g_heapsize)
    {
        for(key=0; key<1024; key++)
        {
            tmp = g_HashBucket.Bucket[key];
            while((NULL != tmp) && (g_heapindex<=g_heapsize))
            {
                array[g_heapindex] = tmp;
                tmp = tmp->next;
                g_heapindex++;
            }

            if(g_heapindex = g_heapsize+1)
            {
                break;
            }
            else
            {
                return;
            }
        }
        heap_build(array);
    }

    for(key=0; key<1024; key++)
    {
        tmp = g_HashBucket.Bucket[key];
        while(NULL != tmp)
        {
            if(tmp->Count > array[1]->Count)
            {
                array[1] = tmp;
                heap_min_ify(array, 1);
            }
            tmp = tmp->next;
        }
    }
  
    return;
}

void file_distribute(FILE *in, int count, FILE *out[])
{
    char buf[256];
    char *ptr;
    int  tmpNO, index;
    assert(NULL != in);
    assert(NULL != out);

    while(NULL != (ptr=fgets(buf, 256, in)))
    {
        tmpNO = atoi(buf);
        index = tmpNO%count;
        fprintf(out[index], "%s", buf);
    }

    return;
}

int hash_key(char *key)
{
    int tmp;
    assert(NULL != key);

    tmp = atoi(key);
    return tmp%1024;
}

int hash_cmp(char *key, PhoneNumber *node)
{
    return strcmp(key, node->Number);
}

void appear_count(FILE *fp)
{
    char buf[256];
    char *ptr;
    int key;
    PhoneNumber *head, *pre, *node;
    assert(NULL != fp);

    while(NULL != (ptr=fgets(buf, sizeof(buf), fp)))
    {
        key = g_HashBucket.HashKey(buf);
        head = g_HashBucket.Bucket[key];
        pre = head;
        while(NULL != pre)
        {
            if(0 == g_HashBucket.HashCmp(buf, pre))
            {
                break;
            }
            pre = pre->next;
        }

        if(NULL == pre)
        {
            node = malloc(sizeof(PhoneNumber));
            if(NULL == node)
            {
                return;
            }
            memset(node, 0, sizeof(PhoneNumber));
            memcpy(node->Number, buf, sizeof(node->Number));
            node->Count = 1;
            node->next = head;
            g_HashBucket.Bucket[key] = node;
        }
        else
        {
            pre->Count++;
        }
    }

    return;
}

void hash_destroy()
{
    int index;
    PhoneNumber *CurNode, *next;
    for(index=0; index<1024; index++)
    {
        CurNode = g_HashBucket.Bucket[index];
        while(NULL != CurNode)
        {
            next = CurNode->next;
            free(CurNode);
            CurNode = next;
        }
        g_HashBucket.Bucket[index] = NULL;
    }

    return;
}

int main(int argc, char *argv[])
{
    int num, FileCount, index;
    PhoneNumber *tmp, **array;
    FILE *in, **out;
    char buf[128];
    assert(3 == argc);

    in = fopen(argv[1], "r");
    FileCount = 16;
    out = malloc(sizeof(FILE *)*FileCount);
    if(NULL == out)
    {
        return -1;
    }
    num = atoi(argv[2]);
    array = malloc(sizeof(PhoneNumber *)*(num+1));
    if(NULL == array)
    {
        free(out);
        return -1;
    }    
    for(index=0; index<FileCount; index++)
    {
        sprintf(buf, "%d.txt", index);
        out[index] = fopen(buf, "w");
        if(NULL == out[index])
        {
            return -1;
        }
        
    }
    
    file_distribute(in, FileCount, out);
    
    for(index=0; index<FileCount; index++)
    {
        appear_count(out[index]);
        find_top(array, &g_HashBucket);
        hash_destroy();
    }

    for(index=1; index<=g_heapindex; index++)
    {
        printf("%s  %d", array[index]->Number, array[index]->Count);
    }

    fclose(in);
    for(index=0; index<FileCount; index++)
    {
        fclose(out[index]);
    }
    
    free(out);
    free(array);
    return 0;
}
