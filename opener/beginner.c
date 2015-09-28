#include <stdio.h>
#include <stdlib.h>

#define MaxStrLength 200
#define StrDelim " "
#define MaxArgNum 20
#define MaxProccessNum 100

typedef struct Proccess
{
	int sleepTime;
	char** argv;
} Proccess;

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount);

/*
 * FIXIT:
 * Называйте ф-и с заглавной: ReadTaskList ...
 * также как и Split
 */
void readTaskList(FILE *inputFile, Proccess* proccessList, int *proccsessNum);
void openProccesses(Proccess* proccessList, int proccessNum);
void deleteProccessList(Proccess* proccessList, int proccessNum);

/*
 * Включите отображение "невидимых" символов.
 * У вас где-то стоят символы табуляции, а где-то пробелы. У вас на компьютере символ табуляции = 4 пробела.
 * У меня не так, поэтому форматирование местами съехало. Либо включите замену всех табов на пробелы, либо включите отображение всех символов
 * и следите за их использованием.
 */

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

void readTaskList(FILE *inputFile, Proccess* proccessList, int* proccessNum)
{
	char string[MaxStrLength];
  /*
   * Обычно компилятор пишет предупреждение, когда есть неиспользуемые переменные.
   */
	int argc, i = 0, j;
	while (fgets(string, MaxStrLength, inputFile) != NULL)
	{
		char* str;
		str = (char*) malloc (MaxStrLength * sizeof(char));
		char** argv = (char**) malloc (MaxArgNum * sizeof (char*));

		char* stringEnding = strstr(string, "\n");
		*stringEnding = '\0';

		char* firstDelim = strstr(string, StrDelim) + 1;
		strcpy(str, firstDelim);

		Split (str, StrDelim, &argv, &argc);
		argv[argc] = NULL;
		
		proccessList[i].sleepTime = atoi(string);
		proccessList[i].argv = argv;
		i++;
	}
	*proccessNum = i;
}

void openProccesses(Proccess* proccessList, int proccessNum)
{
	int i;
	for (i = 0; i < proccessNum; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			sleep(proccessList[i].sleepTime);
			execvp(proccessList[i].argv[0], proccessList[i].argv);
      /*
       * FIXIT:
       * Можно что-то вывести, если не получилось запустить программу.
       */
		}
	}
	/*
   * FIXIT:
   * Нужно дождаться всех дочерних и выписать их статус.
   */
}

void deleteProccessList(Proccess* proccessList, int proccessNum)
{
	int i;
	for (i = 0; i < proccessNum; i++)
	{
		free(proccessList[i].argv[0]);
		free(proccessList[i].argv);
	}
}

int main()
{
	int proccessNum;
	FILE *inputFile = fopen("input.txt", "r");

	Proccess* proccessList = (Proccess*)malloc(sizeof(Proccess) * MaxProccessNum);

/*
 * Я не очень понимаю, зачем ставить слишком много пробелов между строками.
 * Обычно их ставят, что отделить части кода, которые несут разную смысловую нагрузку (и объединить то, что делает общее дело). 
 * Я бы без надобности не разделял строки пустой.
 */
	readTaskList(inputFile, proccessList, &proccessNum);
	openProccesses(proccessList, proccessNum);
	deleteProccessList (proccessList, proccessNum);
	
	free(proccessList);
	return 0;
} 
