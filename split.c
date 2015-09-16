#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount)
{
	char* p = NULL;
	int k = 0;
	p = strtok(string,delimiters);	
	while (p)
		{
    	(*tokens)[k] = p;
		p = strtok(NULL, delimiters);
		k++;
 		}
	*tokensCount = k;
}

int main() {
	int i = 0, tokensCount;
	char string[200] = "", delimiters[100] = "";
	char** words = (char**)malloc(sizeof(char*) * 100);
	gets(string);
	gets(delimiters);
	Split (string, delimiters, &words, &tokensCount);
	for (i = 0; i < tokensCount; i++)
		printf ("%s\n", words[i]);
	free(words);
	return 0;
}

