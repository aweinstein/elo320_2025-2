// Buffer circular
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int read;
    int write;
    int n; // Numero actual de elementos en el buffer
    int size; // Largo total del buffer
    int *data;
} buffer;

buffer *make_buffer(int size);
int get_buffer(buffer *b);
void put_buffer(buffer *b, int a);
int is_empty_buffer(buffer *b);
int is_full_buffer(buffer *b);
void display_buffer(buffer *b);
void destroy_buffer(buffer *b);

int main(void)
{
 buffer *b;
 printf("Buffer circular\n");
 b = make_buffer(2);
 display_buffer(b);
 put_buffer(b, 12);
 put_buffer(b, 34);
 put_buffer(b, 56);
 display_buffer(b);
 int d = get_buffer(b);
 printf("Leimos del buffer %d\n", d);
 display_buffer(b);
 return 0;   
}


buffer *make_buffer(int size)
{
 buffer *b = malloc(sizeof(buffer));
 b->read = 0;
 b->write = 0;
 b->n = 0;
 b->size = size;   
 b->data = malloc(size * sizeof(int));
 return b;
}

// quien llama es responsable de verificar que existen datos en el buffer
int get_buffer(buffer *b)
{
  int d;
  if(is_empty_buffer(b)) {
      printf("Error: buffer no tiene datos\n");
  } else {
    d = b->data[b->read];
    b->n--; // equivalente a b->n = b->n - 1
    b->read = (b->read + 1) % b->size;
    return d;
  }
}


void put_buffer(buffer *b, int a)
{
  if(is_full_buffer(b)) {
    printf("Error: buffer lleno!\n");
  } else {
    b->data[b->write] = a;
    b->n++;
    b->write = (b->write + 1) % b->size;
  } 
}

int is_empty_buffer(buffer *b)
{
  return (b->n == 0);    
}

int is_full_buffer(buffer *b)
{
  return (b->n == b->size);    
}

void display_buffer(buffer *b)
{
  int i, cursor;
  cursor = b->read;
  printf("Buffer begin ");
  for(i=0; i < b->n; i++) {
    printf("%d ", b->data[cursor]);
    cursor = (cursor + 1) % b->size;
  }
  printf(" buffer end\n");
}

void destroy_buffer(buffer *b)
{
 free(b->data);
 free(b);   
}

