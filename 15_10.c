#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

/*
 * Нормально. Ваш код изначально вроде бы тоже рабочий. 
 * Я чуть поправил. Обычно как-то так используют openmp.
 * 
 * Если когда-нибудь возникнет желание нормально разобраться с omp, можете просмотреть
 * https://www.youtube.com/playlist?list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG
 */

const int K = 4;
const int N = 1e6;

int* array;

typedef struct Number 
{
    int result;
    int square;
} Number;

int main()
{
    int j;
    Number interval[K];
    float average = 0.0, dispersion = 0.0, calculation = 0.0, calculationSquare = 0.0;
    int reading[K];
    array = (int*)malloc(sizeof(int) * N);
    srand(time(NULL));

    for (j = 0; j < N; j++)
        array[j] = rand() % 2;

    #pragma omp parallel num_threads(K)
    {
        int thread_id = omp_get_thread_num();
        printf("thread_id = %d\n", thread_id);
        interval[thread_id].result = 0.0;
        interval[thread_id].square = 0.0;
        
        int i = 0;
        #pragma omp for
        for (i = 0; i < N; i++)
        {
            interval[thread_id].result += array[i];
            interval[thread_id].square += array[i] * array[i];
        }
    }
    
    for (j = 0; j < K; j++)
    { 
        calculation += interval[j].result;
        calculationSquare += interval[j].square;
    }

    average = calculation / N;
    float averageSquare = calculationSquare / N;
    dispersion = averageSquare - average * average;
    printf ("Average = %f\nAverage square = %f\nSquare of average = %f\nDispersion =  %f\n",
        average, averageSquare, average * average, dispersion);
    free(array);
    return 0;
}
