#include <stdio.h>
#include <unistd.h>

int main()
{
	int t;
	pid_t pid = fork();
	if (pid == 0) 
		execlp ("ls", "ls", "-al", NULL);
	wait(& t);
	execlp ("pwd", "pwd", NULL);	
	printf("Error\n");
return 0;
} 
