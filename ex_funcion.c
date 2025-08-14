#include <stdio.h>

/* Declaracion de las funciones */
int suma (int, int); // prototipo de la funcion

void main(void)
{
    int j, k;
    j = 5;
    k = 23;
    printf("Resultado j + k = %d \n", suma(j, k));
}

int suma(int a, int b)
{
    int c; // Variable local
    c = a + b;
    return c;
}
