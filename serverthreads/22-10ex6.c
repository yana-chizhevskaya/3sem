#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define LAST_MESSAGE 255 
typedef struct Message {
        float first;
        float second;
    } Message;

typedef struct Data {
        Message message;
        pid_t pid;
        float digit;
    } Data;

int main() {
    int msqid; 
    Message message;
    char pathname[] = "22-10ex6.c"; 
    key_t key; 

    int i, len; 
    int maxlen = 81;
    
    struct mybuf {
        long mtype;
        Data data;
    } mybuf;
    
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    } 

    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }
	while(1)
	{
		scanf("%f%f", &(mybuf.data.message.first), &(mybuf.data.message.second));
		mybuf.mtype = 1;
		len = sizeof(Data);
		mybuf.data.pid = getpid();
		if (msgsnd(msqid, (struct mybuf *) &mybuf, len, 0) < 0) {
		    printf("Can\'t send message to queue\n");
		    msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
		    exit(-1);
		}
		
		msgrcv(msqid, (struct mybuf *)&mybuf, maxlen, getpid(), 0);
		printf("%f\n", mybuf.data.digit);
	}  
  return 0;
} 

