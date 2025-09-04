#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10

typedef struct {
    int n;  // Numero de elementos en el stack
    int data[MAXSIZE]; // Tarea: Modificar para largo variable
} stack;

// Prototipo de funciones
stack *make_stack(void);
void push(stack *sp, int a);
int pop(stack *sp);
void display(stack *sp);

int main(void)
{
 printf("Stack\n");
 stack *s;
 s = make_stack();
 push(s, 12);
 push(s, 34);
 display(s);
 int x = pop(s);
 printf("Resultado del pop: %d\n", x);
 display(s); 
 
 // Tarea: verificar los casos limite
 
 free(s);
 return 0;
}


stack *make_stack(void)
{
 stack *sp = malloc(sizeof(stack));
 // Falta manejar el caso en que retorna NULL!
 sp->n = 0;
 return sp;   
}


void push(stack *sp, int a)
{
 if(sp->n == MAXSIZE) {
   fputs("Error: No se puede agregar mas elementos al stack", stderr);
   exit(1);
 } else {
   sp->data[sp->n++] = a;
 }
}


int pop(stack *sp)
{
 if(sp->n == 0) {
   fputs("Error: Stack vacio", stderr);
   exit(2);
 } else {
   return sp->data[--(sp->n)];
 }
}



void display(stack *sp) 
{
  printf("--------\n");
  for(int i=sp->n - 1; i >=0; i--)
    printf("%d\n", sp->data[i]);
  printf("--------\n");  
}


