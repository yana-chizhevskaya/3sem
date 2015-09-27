#include <stdio.h>
#include <string.h>

int main()
{
  char *p;

  p = strtok("Травка зеленеет, солнышко блестит", " ");
  printf("%p\n",p);
  do {
    p = strtok('\0', ", ");
    if(p) printf("|%s", p);
  } while(p);

  return 0;
}
