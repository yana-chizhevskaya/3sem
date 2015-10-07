#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define K 4
#define N 3e8

int* array;

typedef struct Number 
{
    int begin;
    int end;
    int result;
    int square;
} Number;


void* my_thread(void* interval) 
{
    Number* a = (Number*)interval;
    int i = 0;
    for (i = a->begin; i < a->end; i++)
    {     
        a->result += array[i];
        a->square += array[i] * array[i];    
    }
    return NULL;
}

int main()
{
    pthread_t thread_id[K];
    int j, i;
    Number interval[K];
    float average = 0.0, dispersion, calculation = 0.0, calculationSquare = 0.0;
    int reading[K];
    array = (int*)malloc(sizeof(int) * N);
    
    srand(time(NULL));
    clock_t startTime = clock();
    for (j = 0; j < N; j++)
        array[j] = rand() % 2;

    for (i = 0; i < K; i++)
    {
        interval[i].begin = (N / K) * i;
        interval[i].end = (N / K) * (i + 1);
        interval[i].result = 0.0;
        interval[i].square = 0.0;
        reading[i] = pthread_create(thread_id + i, (pthread_attr_t *)NULL, my_thread, (void*)(interval + i));
    }
    for (i = 0; i < K; i++)
        pthread_join(thread_id[i] , (void **) NULL);
    for (j = 0; j < K; j++)    
    { 
        calculation += interval[j].result;
        calculationSquare += interval[j].square;
    }
    average = calculation / N;
    float averageSquare = calculationSquare / N;
    dispersion = averageSquare - average * average;
    
    clock_t finishTime = clock();
    printf ("Average = %f\nAverage square = %f\nSquare of average = %f\nDispersion =  %f\nTime elapsed = %f\n",
        average, averageSquare, average * average, dispersion, double(finishTime - startTime) / CLOCKS_PER_SEC);
    free(array);
    return 0;
}
