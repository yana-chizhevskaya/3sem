#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <string.h>
#include <stdlib.h>

#define LENGHT 64

int bitNum = 0;
pid_t pid;
char s[LENGHT] = {0};
char result[LENGHT] = {0};

void readBit(int nsig)
{
	if (nsig == SIGUSR1)
    {
    }
    if (nsig == SIGUSR2)
        result[bitNum / 8] = result[bitNum / 8] | (1 << (bitNum % 8));
    bitNum++;
    kill(pid, SIGINT);

    if (bitNum / 8 == LENGHT)
    {
    	printf("%s\n", result);
    	//exit(0);
    }
}

void sendBit()
{
    char bit;
    bit = s[bitNum / 8] & (1 << bitNum % 8);
    bitNum++;
    kill(pid, (bit) ? SIGUSR2 : SIGUSR1);
    
    if (bitNum / 8 == LENGHT)
        exit(0);
        
}

int main()
{

    signal(SIGUSR1, readBit);
    signal(SIGUSR2, readBit);
    signal(SIGINT, sendBit);
    
    pid = getpid();
    pid_t new = fork();

    if (new != 0) 
    {
        pid = new;
		gets(s);
        sendBit();
    }

    while(1);
    return 0;
}
