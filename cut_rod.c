#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int gOptimalEarning[128];
int gOptimalCut[128];

int bottom_up_cut_rod(int PriceList[], int length)
{
    int index, index2, earning, len;
    assert(NULL != PriceList);

    memset(gOptimalEarning, 0, sizeof(gOptimalEarning));
    memset(gOptimalCut, 0, sizeof(gOptimalCut));
    for(index=1; index<=length; index++)
    {
        earning = 0;
        len = 0;
        for(index2=1; index2<=index; index2++)
        {
            if(earning < (PriceList[index2]+gOptimalEarning[index-index2]))
            {
                earning = PriceList[index2]+gOptimalEarning[index-index2];
                len = index2;
            }
        }
        gOptimalEarning[index] = earning;
        gOptimalCut[index] = len;
    }

    return earning;
}

void print_cut_rod_sulotion(int PriceList[], int length)
{
    int MaxEarning, len;
    assert(NULL != PriceList);

    MaxEarning = bottom_up_cut_rod(PriceList, length);
    printf("max earning is: %d\n", MaxEarning);
    printf("optimal cut sulotion is:\n");
    len = length;
    while(len>0)
    {
        printf("%d  ", gOptimalCut[len]);
        len -= gOptimalCut[len];
    }
    printf("\n");

    return;
}

int main(int argc, char *argv[])
{
    int PriceList[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int length;
    assert(2 == argc);

    length = atoi(argv[1]);
    print_cut_rod_sulotion(PriceList, length);

    return 0;
}
