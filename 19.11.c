#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LENGHT 1000
#define PORT 51001

int main(int argc, char **argv)
{
    int sockfd;
    int n;
    int i;
    char sendline[MAX_LENGHT], recvline[MAX_LENGHT];
    struct sockaddr_in servaddr;
    
    if(argc != 2)
    {
        printf("usage: ./a.out <IP>\n");
        exit(1);
    }
    
    bzero(sendline, MAX_LENGHT);
    bzero(recvline, MAX_LENGHT);
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror(NULL);
        exit(1);
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0)
    {
        printf("Invalid IP address\n");
        close(sockfd);
        exit(1);
    }
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    while(1)
    {
        printf("Your action: ");
        fflush(stdin);
        fgets(sendline, MAX_LENGHT, stdin);
        if((n = write(sockfd, sendline, strlen(sendline) + 1)) < 0)
        {
            perror("cant wrrite\n");
            close(sockfd);
            exit(1);
        }
        if((n = read(sockfd, recvline, MAX_LENGHT - 1)) < 0)
        {
            perror("cant read\n");
            close(sockfd);
            exit(1);
        }
        printf("%s", recvline);
    }
    
    close(sockfd);
    return 0;
}

