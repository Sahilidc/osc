#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 5   // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer
sem_t empty;
sem_t full;
int in = 0, out = 0, buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;

    for (int i = 0; i < MaxItems; i++)
    {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{
    for (int i = 0; i < MaxItems; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);
    int a[5] = {1, 2, 3, 4, 5}; // Just used for numbering the producer and consumer
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(con[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

// Output:
/*
Producer 1: Insert Item 41 at 0
Producer 5: Insert Item 41 at 1
Consumer 2: Remove Item 41 from 0
Consumer 1: Remove Item 41 from 1
Producer 1: Insert Item 18467 at 2
Producer 4: Insert Item 41 at 3
Producer 2: Insert Item 41 at 4
Producer 5: Insert Item 18467 at 0
Producer 3: Insert Item 41 at 1
Consumer 2: Remove Item 18467 from 2
Consumer 4: Remove Item 41 from 3
Consumer 1: Remove Item 41 from 4
Producer 2: Insert Item 18467 at 2
Consumer 5: Remove Item 18467 from 0
Producer 1: Insert Item 6334 at 3
Consumer 4: Remove Item 41 from 1
Consumer 3: Remove Item 18467 from 2
Consumer 2: Remove Item 6334 from 3
Producer 5: Insert Item 6334 at 4
Producer 4: Insert Item 18467 at 0
Producer 3: Insert Item 18467 at 1
Producer 2: Insert Item 6334 at 2
Consumer 3: Remove Item 6334 from 4
Consumer 1: Remove Item 18467 from 0
Consumer 5: Remove Item 18467 from 1
Consumer 4: Remove Item 6334 from 2
Producer 1: Insert Item 26500 at 3
Producer 5: Insert Item 26500 at 4
Consumer 3: Remove Item 26500 from 3
Producer 3: Insert Item 6334 at 0
Producer 2: Insert Item 26500 at 1
Consumer 2: Remove Item 26500 from 4
Producer 4: Insert Item 6334 at 2
Producer 1: Insert Item 19169 at 3
Consumer 3: Remove Item 6334 from 0
Consumer 5: Remove Item 26500 from 1
Producer 5: Insert Item 19169 at 4
Consumer 4: Remove Item 6334 from 2
Consumer 1: Remove Item 19169 from 3
Producer 3: Insert Item 26500 at 0
Producer 3: Insert Item 19169 at 1
Consumer 2: Remove Item 19169 from 4
Producer 4: Insert Item 26500 at 2
Producer 4: Insert Item 19169 at 3
Consumer 3: Remove Item 26500 from 0
Consumer 5: Remove Item 19169 from 1
Producer 2: Insert Item 19169 at 4
Consumer 4: Remove Item 26500 from 2
Consumer 1: Remove Item 19169 from 3
Consumer 5: Remove Item 19169 from 4
*/