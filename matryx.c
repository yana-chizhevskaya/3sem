#include <stdio.h>


int main (){
  int i=0;
  int **dead;
  dead=(int**)malloc(1000*sizeof(int*));
  for(i=0; i<1000; i++)
      dead[i]=(int*)malloc(1000*sizeof(int));
  return 0;
}
