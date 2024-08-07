#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 3
#define MAX_ITEM 3

sem_t empty;
sem_t full;
int in = 0, out = 0;
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex;

void *producer(void *pro)
{
      int item;
      for (int i = 0; i < MAX_ITEM; i++)
      {
            item = rand() % 100;
            sem_wait(&empty);
            pthread_mutex_lock(&mutex);
            buffer[in] = item;
            printf("Producer %d: inserted item %d at %d\n", *((int *)pro), buffer[in], in);
            in = (in + 1) % BUFFER_SIZE;
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
      }
      return NULL;
}

void *consumer(void *con)
{
      for (int i = 0; i < MAX_ITEM; i++)
      {
            sem_wait(&full);
            pthread_mutex_lock(&mutex);
            int item = buffer[out];
            printf("Consumer %d: removed %d from %d\n", *((int *)con), item, out);
            out = (out + 1) % BUFFER_SIZE;
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
      }
      return NULL;
}

int main()
{
      pthread_t pro[3], con[3];
      pthread_mutex_init(&mutex, NULL);
      sem_init(&empty, 0, BUFFER_SIZE);
      sem_init(&full, 0, 0);

      int a[3] = {1, 2, 3};

      for (int i = 0; i < 3; i++)
            pthread_create(&pro[i], NULL, producer, (void *)&a[i]);

      for (int i = 0; i < 3; i++)
            pthread_create(&con[i], NULL, consumer, (void *)&a[i]);

      for (int i = 0; i < 3; i++)
            pthread_join(pro[i], NULL);
      for (int i = 0; i < 3; i++)
            pthread_join(con[i], NULL);

      pthread_mutex_destroy(&mutex);
      sem_destroy(&empty);
      sem_destroy(&full);

      return 0;
}
