#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sem.h>

#define MAX_LENGHT 1000
#define PORT 51001

int balance = 1e5, newsockfd, sockfd, n;

void* my_thread(void* arg) {

	key_t key; 
	int semid;
	char pathname[] = "19.11-2.c"; 
    int* newsockfd = (int*)arg;

	char line[MAX_LENGHT];
	
	if((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
    {
       printf("Can\'t create semaphore\n");
       exit(-1);
    }
    
    struct sembuf mybuf;

	 while((n = read(*newsockfd, line, MAX_LENGHT - 1)) > 0)
     {
       	mybuf.sem_op = 1;
    	mybuf.sem_flg = 0;
    	mybuf.sem_num = 0;
    	
    	if (semop(semid , &mybuf , 1) < 0) 
        {
            printf("Can`t wait for condition\n");
            exit(-1);
        }
        printf("%s", line);
		int amount = atoi(line);
		
		if (amount > 0)
		{
			balance += amount;
			strcpy(line, "You return dollars in the bank!\n");
		}
		else 
		{
			if (balance < -amount)
				strcpy(line, "Sorry, we can't lend dollars to you\n");
			else 
			{
				balance += amount;
				strcpy(line, "You borrow dollars from the bank!\n");
			}
		}
		mybuf.sem_op = -1;
        mybuf.sem_flg = 0;
        mybuf.sem_num = 0;
        
        if (semop(semid , &mybuf , 1) < 0) 
        {
            printf("Can`t wait for condition\n");
            exit(-1);
        }
		if((n = write(*newsockfd, line, strlen(line) + 1)) < 0)
		        {
		            perror(NULL);
		            close(sockfd);
		            exit(1);
		        }
		
     	bzero(line, MAX_LENGHT);
	}
    if(n < 0)
    {
    	perror(NULL);
        close(sockfd);
        exit(1);
    }
    printf("%s", line);
    close(*newsockfd);
    return NULL;
}

int main(int argc, char **argv)
{
    int i;
    char line[MAX_LENGHT];
    int clilen, result;
    pthread_t thread_id;
    
    struct sockaddr_in servaddr, cliaddr;
    
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror(NULL);
        exit(1);
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    if(listen(sockfd, 5) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
       
    
    while(1)
    {
        clilen = sizeof(cliaddr);
        int* newsockfd = (int*)malloc(sizeof(int));
	/*
	 * Придумали халявный способ с malloc`ом и используете который раз :)
	 */
        if((*newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen)) < 0)
        {
            perror(NULL);
            close(sockfd);
            exit(1);
        }
		printf("someone's connected, %d\n", *newsockfd);
		result = pthread_create(&thread_id, (pthread_attr_t *)NULL, my_thread, newsockfd);
    }  
                
    
    close(sockfd);
    return 0;
}


