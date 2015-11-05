#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void ReadTaskList(FILE *inputFile, Proccess* proccessList, int *proccsessNum);
void OpenProccesses(Proccess* proccessList, int proccessNum);
void DeleteProccessList(Proccess* proccessList, int proccessNum);


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

void ReadTaskList(FILE *inputFile, Proccess* proccessList, int* proccessNum)
{
	char string[MaxStrLength];
	int argc, i = 0;
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

void OpenProccesses(Proccess* proccessList, int proccessNum)
{
	int i, status, id[MaxProccessNum];
    pid_t childID;

	for (i = 0; i < proccessNum; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			sleep(proccessList[i].sleepTime);
			execvp(proccessList[i].argv[0], proccessList[i].argv);
            printf ("ERROR! Can't open the program \"%s\".\n", proccessList[i].argv[0]);
            exit(1);
		}
        id[i] = pid;
    }

    do 
	{
	    childID = wait(&status);
        for (i = 0; i < proccessNum; i++)
        {
            if (childID == id[i])
                printf ("\nProcess %s ended and returned %d\n", proccessList[i].argv[0], status >> 8);
        }
	} while (childID != -1);
}

void DeleteProccessList(Proccess* proccessList, int proccessNum)
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

	ReadTaskList(inputFile, proccessList, &proccessNum);
	OpenProccesses(proccessList, proccessNum);
	DeleteProccessList (proccessList, proccessNum);
	
	free(proccessList);

	return 0;
} 
