#include <stdio.h>

int main(void)
{
 int a[10];
 int *p;
 int i;
 
 //p = a;
 p = &a[0];
 for(i=0; i<10; i++)
 {
  printf("a[%d] -> 0x%p \n", i, p++); 
 }
   
 return 0; 
}
