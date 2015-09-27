#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a = 0;
	/*int pid;
	pid = fork();
	if (pid == -1)
		printf ("ERROR\n");
	else 
		if (pid == 0) 
			printf ("kid\n%d\n", pid);
		else 
			printf ("parent\n%d\n", pid);
	/*printf ("\n%d\n", getpid(a));*/
	printf ("Hello, \n");
	fork();
	printf ("world!\n");
	return 0;
}
