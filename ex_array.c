#include <stdio.h>

void main(void)
{
    int a[5] = {10, 20, 30, 40, 50};

    printf("%d \n", a[2]);
    a[2] = 3;
    printf("%d \n", a[2]);
    // Cuidado!!
    printf("%d \n", a[1000]);
    //a[1000] = 2;
    printf("xxx %d \n", a[1000]);
}