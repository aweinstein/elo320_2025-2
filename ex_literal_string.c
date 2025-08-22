#include <stdio.h>
// Precaucion con los strings literales

int main(void)
{
    /* El string literal "Hola" se copia al arreglo de caracteres s1. 
    En cambio, el puntero s2 apunta al string literal "Chao". 
    Los string literales no se pueden modificar. Si intentamos 
    modificar un string literal, el programa se cae. */
    char s1[] = "Hola";
    char* s2 = "Chao";
    
    printf("%s %s\n", s1, s2); // No problema
    s1[0] = 'X';
    printf("%s %s\n", s1, s2); // Todavia OK
    s2[0] = 'X'; // Modificamos un area de memoria que es un string literal!
                 // El programa deja de funcionar
    printf("%s %s\n", s1, s2);
    return 0;
}