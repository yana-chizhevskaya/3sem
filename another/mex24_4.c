#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fd1[2], fd2[2];
	pipe(fd1);
	pipe(fd2);
	
	int child_wr = fd1[1];
	int child_rd = fd2[0];

	int parent_wr = fd2[1];
	int parent_rd = fd1[0];

	pid_t id = fork();
	
	if (id == 0)
	{
		int a = 15, b = 385, c;
		write (child_wr, &a, sizeof(int));
		write (child_wr, &b, sizeof(int));
		read (child_rd, &c, sizeof (int));
		printf ("%d\n", c);
		exit (0);
	}
	else 
	{
		int a, b, c;
		read(parent_rd, &a, sizeof (int));
		read(parent_rd, &b, sizeof (int));
		c = a + b;
		write(parent_wr, &c, sizeof (int));
	}

	return 0;
}
