#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount)
{
	char* p = NULL;
	int k;
	p = strtok(string,delimiters);
  /*
   * Непонятно, что вы этим хотели сказать.
   * Если вдруг без этого не обойтись, то можно было бы воспользоваться тернарным оператором
   * k = p ? 1 : 0;
   */
	if (p)
		k = 1;
	else
		k = 0;	
	while (p)
		{
      /*
       * по-моему запись (*tokens)[k] более понятна, чем *(*tokens+k)
       */
    	*(*tokens+k) = p;
		p = strtok(NULL, delimiters);
		k++;
 		}
	*tokensCount = k;
}

int main() {
	int i = 0, n;
  /*
   * FIXIT: Не заводите в коде магических чисел, о смысле которых надо докадываться. Объявите константу MaxStringSize и MaxDelimetersCount соотвественно.
   * + старайтесь называть переменные более осмысленно: почему бы вместо n не написать tokensCount, ведь за ней ровно это кроетя.
   */
	char string[200] = "", delimiters[100] = "";
  /*
   * FIXIT:
   * ставьте отступы вокруг бинарных операторов
   */
	char** words = (char**)malloc(sizeof(char*)*100);
	gets(string);
	gets(delimiters);
	Split (string, delimiters, &words, &n);
  /*
   * FIXIT: почему цикл от 1, а не от 0?
   * вы где-то лишний раз увеличили n на единицу. 
   * ф-я split должна вернуть число слов, а не число слов плюс 1.
   */
	for (i = 1; i < n; i++)
		printf ("%s\n", words[i]);
  
  /*
   * надо освободить память
   */
	printf("\n");
	return 0;
}


