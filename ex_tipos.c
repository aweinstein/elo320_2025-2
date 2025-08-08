#include <stdio.h>

void main(void)
{
    int a = 2;
    int b, c;
    double x, y;
    char d;
    b = 12;
    x = 1.23;
    d = 'a';    
    printf("Ejemplo de tipos de datos \n");
    printf("a = %d b = %d \n", a, b);
    printf("x = %.2f\n", x);
    x = 99.5;
    printf("x = %.2f\n", x); // Esto tambien es un comentario
    
    /* Veamos el tamanio de las variables 
    Usaremos sizeof
    */
    printf("\n\nSize de un entero: %zu", sizeof(int));
    printf("\n\nSize de un entero: %zu", sizeof(a));
    printf("\n\nSize de un entero: %zu", sizeof(long long int));
}