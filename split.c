#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount)
{
	char* p = NULL;
	int k;
	p = strtok(string,delimiters);
	if (p)
		k = 1;
	else
		k = 0;	
	while (p)
		{
    	*(*tokens+k) = p;
		p = strtok(NULL, delimiters);
		k++;
 		}
	*tokensCount = k;
}

int main() {
	int i = 0, n;
	char string[200] = "", delimiters[100] = "";
	char** words = (char**)malloc(sizeof(char*)*100);
	gets(string);
	gets(delimiters);
	Split (string, delimiters, &words, &n);
	for (i = 1; i < n; i++)
		printf ("%s\n", words[i]);
	printf("\n");
	return 0;
}


