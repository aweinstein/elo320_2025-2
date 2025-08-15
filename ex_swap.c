#include <stdio.h>

void swap(int *a, int *b);
void print_a_and_b(int a, int b);

int main(void)
{
    int a, b;
    a = 10;
    b = 20;
    printf("Probando la función swap...\n");
    printf("Antes del swap:\n");
    print_a_and_b(a, b);
    printf("Despues del swap:\n");
    swap(&a, &b);
    print_a_and_b(a, b);
    return 0;
}


void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_a_and_b(int a, int b)
{
    printf("a = %d, b = %d\n", a, b);
}

