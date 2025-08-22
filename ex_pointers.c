#include <stdio.h>

int main(void)
{
  // Arreglo de punteros a strings
  char * names[] = {"Juan", "Valentina", "Rocio", "Tomas"};
  
  int size = sizeof(names) / sizeof(names[0]); //
  printf("El arreglo tiene %d elementos\n", size);
  for(int i=0; i < size; i++)
    //printf("%d -> %s\n", i + 1, *(names + i));
    printf("%d -> %s\n", i + 1, names[i]);
  return 0;   
}