#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N, i, status;
	pid_t childID;
	pid_t pid;
	scanf("%d", &N);

	for (i = 0 ; i < N; i++) 
	{
		pid = fork();
		if (pid != 0) 
			break;
		printf("New proccess was created: %d  by: %d\n" , getpid(), getppid());
		
	}
	while ((childID = wait(&status))  != -1) 
	{
		printf("[Child proccess was ended: %d] [Parent proccess: %d]\n" , childID, getpid());
		exit(0);
	}
  return 0;
} 
