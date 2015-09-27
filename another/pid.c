#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N = 4, i, status;
	pid_t pid = fork();

	for (i = 0 ; i < N; ++i) 
	{
		if (pid == 0) 
		{
			pid = fork();
			sleep(i + 1);
			printf("%d  %d\n" , getpid(), getppid());
			exit(0);
		}
	}
	
	pid_t childID;
	do 
	{
	childID = wait(&status);
	printf ("\n%d\n", childID); 
	} while (childID != -1);
return 0;
} 
