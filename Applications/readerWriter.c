#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt;
pthread_mutex_t mutex;
int count = 1;
int numReader = 0;

void *writer(void *parameter)
{
      int id = *((int *)parameter);
      sem_wait(&wrt);
      count *= 2;
      printf("Writer %d modified count to %d\n", id, count);
      sem_post(&wrt);
      pthread_exit(NULL);
}

void *reader(void *parameter)
{
      int id = *((int *)parameter);
      pthread_mutex_lock(&mutex);
      numReader++;
      if (numReader == 1)
      {
            sem_wait(&wrt);
      }
      pthread_mutex_unlock(&mutex);

      printf("Reader %d: read count as %d\n", id, count);

      pthread_mutex_lock(&mutex);
      numReader--;
      if (numReader == 0)
      {
            sem_post(&wrt);
      }
      pthread_mutex_unlock(&mutex);

      pthread_exit(NULL);
}

int main()
{
      pthread_t read[3], write[3];
      pthread_mutex_init(&mutex, NULL);
      sem_init(&wrt, 0, 1);
      int a[3] = {1, 2, 3};

      // Create writer threads
      for (int i = 0; i < 3; i++)
      {
            pthread_create(&write[i], NULL, writer, (void *)&a[i]);
      }

      // Create reader threads
      for (int i = 0; i < 3; i++)
      {
            pthread_create(&read[i], NULL, reader, (void *)&a[i]);
      }

      // Join writer threads
      for (int i = 0; i < 3; i++)
      {
            pthread_join(write[i], NULL);
      }

      // Join reader threads
      for (int i = 0; i < 3; i++)
      {
            pthread_join(read[i], NULL);
      }

      pthread_mutex_destroy(&mutex);
      sem_destroy(&wrt);

      return 0;
}
