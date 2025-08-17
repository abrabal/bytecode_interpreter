#include <stdio.h>


int main()
{
    int mask1 = 0x40;
    int mask2 = 0x4;
    int num = 68;
    int new_mask = num &(3 << 6);

    printf("%d", new_mask);
}