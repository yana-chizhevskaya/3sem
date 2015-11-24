#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int sockfd;
  int clilen, n, i = 0;
  char line[1000];
  char buf[100];
  struct sockaddr_in servaddr, cliaddr;
  
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(62000);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror(NULL);
    exit(1);
  } else
  {
    printf("Sock fd:%d\n", sockfd);
  }
  
  if (bind(sockfd, (struct sockaddr*) &servaddr, 
    sizeof(servaddr)) < 0)
  {
    perror(NULL);
    close(sockfd);
    exit(1);
  }
  
  struct User
  {
    int port;
    int ip;
  }; 
  
  struct User users[100];
  int userscount = 0;
  clilen = sizeof(cliaddr);
  while (1)
  {
	bzero(line, 1000);
    if ((n = recvfrom(sockfd, line, 999, 0, (struct sockaddr*)&cliaddr, &clilen)) < 0)
    {
      perror(NULL);
      close(sockfd);
      exit(1);
    }
    printf("%s", line);
  
    
		int newUser = -1;
		
		for(i = 0; i < userscount; i++)
		{
		  if(cliaddr.sin_port == users[i].port && cliaddr.sin_addr.s_addr == users[i].ip)
		    newUser = i;
		}
		
		if(newUser < 0)
		{
		  users[userscount].port = cliaddr.sin_port; 
		  users[userscount].ip = cliaddr.sin_addr.s_addr;
		  printf("someone's connected, ip %d, port, %d\n", users[userscount].ip, users[userscount].port);
		  userscount++;
		}
		else
		{
		  for(i = 0; i < userscount; i++)
		  {
			if(i != newUser)
			{
				printf("sending message %s to ip %d, port %d", line, users[i].ip, users[i].port);
				bzero(&cliaddr, sizeof(cliaddr));
  				cliaddr.sin_family = AF_INET;
			  	cliaddr.sin_port = users[i].port;
			  	cliaddr.sin_addr.s_addr = users[i].ip;

		 		if (sendto(sockfd, line, strlen(line) + 1, 0, (struct 			 
								sockaddr*)&cliaddr, clilen) < 0)
		   		{
				  perror(NULL);
				  close(sockfd);
				  exit(1);
		  		 }
			}
		  }
		}
	
	}  
	  
  return 0;
}
