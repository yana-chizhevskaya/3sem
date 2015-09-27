#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N, i, status;
	pid_t childID;
	scanf("%d",&N);
	pid_t pid = fork();
	for (i = 0 ; i < N; ++i) 
	{
		pid_t pid = fork();
		if (pid == 0) 
		{
			pid_t pid = fork();
			sleep(i + 1);
			childID = wait(&status);
			printf("%d\n" , i);
		}
		else break;
	}

	do 
	{
	childID = wait(&status);
	printf ("\n%d\n", childID); 
	} while (childID != -1);
return 0;
} 
