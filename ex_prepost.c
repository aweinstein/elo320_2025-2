#include <stdio.h>

int suma(int a, int b)
{
    int c; // Variable local
    c = a + b;
    return c;
}

void main(void)
{
    int a = 10;
    int b = 20;
    int c = 10;
    printf("Preincremento: %d \n", suma(++a, b));
    printf("Postincremento: %d \n", suma(c++, b));  
    
}