#include <stdio.h>
#include <stdlib.h>

int *give_me_mem(int);

int main(void)
{
 int *data;
 int largo = 10;
 printf("Probando malloc.\n");   
 data = give_me_mem(largo);
 for(int i=0; i < largo; i++)
   //printf("%d -> %d \n", i, *(data + i)); 
   printf("%d -> %d \n", i, data[i]);  
 free(data);
 return 0;   
}

// Entrega un puntero a un arreglo de N enteros.
// El puntero se inicializa con la secuencia 0, 10, 20, ...
int *give_me_mem(int N)
{
  int *p;
  p = malloc(N * sizeof(int)); // Falta verificar que p sea distinto de NULL
  for(int i=0; i<N; i++)
    *(p + i) = 10 * i;
  
  return p;
}