#include <stdio.h>
#include <string.h>
	
void Split(char* string, char* delimiters, char*** tokens, int* tokensCount){
		char* p = NULL;
		p = strtok(string,delimiters);	
		while (p) {
      if (p) printf("%s\n", p);
			p = strtok(NULL, delimiters);
  }

}



	int main() {
	
	char string[200] = "", delimiters[100] = "";
	char*** words;
	int n = 0;
	gets(string);
	gets(delimiters);
	Split (string, delimiters, words, &n);

return 0;
}


