#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define LAST_MESSAGE 255
#define N 2

typedef struct Message {
        float first;
        float second;
    } Message;

typedef struct Data {
        Message message;
        pid_t pid;
        float digit;
    } Data;
typedef struct mybuf {
        long mtype;
        Data data;
    } mybuf;

int msqid, semid;

void* my_thread(void* receive) {
	struct sembuf mysembuf;
    
    mysembuf.sem_flg = 0;
    mysembuf.sem_num = 0;
    mysembuf.sem_op  = -1;
    if(semop(semid, &mysembuf, 1) < 0) 
    {
        printf("Can`t wait for condition\n");
        semctl(semid, IPC_RMID, 0);         
        exit(-1);
    }
	int len = sizeof(Data);
    mybuf* a = (mybuf*)receive;
    sleep(10);
    a->data.digit = a->data.message.first * a->data.message.second;
    a->mtype = a->data.pid; 
    msgsnd(msqid, (struct msgbuf*)a, len, 0);
    free(a);
    
    mysembuf.sem_op = 1;
    if(semop(semid, &mysembuf, 1) < 0) 
    {
        printf("Can`t wait for condition\n");
        semctl(semid, IPC_RMID, 0);         
        exit(-1);
    }
    return NULL;
}

int main() {
    pthread_t thread_id;
    char pathname[] = "22-10ex6.c"; 
    key_t key; 
    int len, maxlen, result; 
    mybuf* a;
    if((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    len = sizeof(Data);
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    
    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
    {
       printf("Can\'t create semaphore\n");
       exit(-1);
    }
    struct sembuf mysembuf;
    
    mysembuf.sem_flg = 0;
    mysembuf.sem_num = 0;
    mysembuf.sem_op  = N;
    if(semop(semid, &mysembuf, 1) < 0) 
    {
        printf("Can`t wait for condition\n");
        semctl(semid, IPC_RMID, 0);         
        exit(-1);
    }
    
    maxlen = sizeof(Data);

   while(1) {
    a = (mybuf*)malloc(sizeof(mybuf));
    if ((len = msgrcv(msqid, (mybuf *)a, maxlen, 1, 0)) < 0) {
        printf("Can\'t receive message from queue\n");
        exit(-1);
    }
    printf("%f   %f\n", a->data.message.first, a->data.message.second);
    result = pthread_create(&thread_id, (pthread_attr_t *)NULL, my_thread, a);
    }
  
  return 0;
} 

