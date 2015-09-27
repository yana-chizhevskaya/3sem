#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd, n;
	char* string;
	scanf("%d",&n);
	string = (char*)malloc(sizeof(char) * (n + 1));
	umask(0);
	if ( (fd = open("myfile.in" , O_RDONLY)) < 0 ) 
	{
		printf("Can`t open file\n");
		exit(-1);
	}
	int a;
	while (( a = read(fd, (void*)string , n)) > 0)
	{
		string[a] = '\0';
		printf("%s\n", string);
	}
	return 0;
}
