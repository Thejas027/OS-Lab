#include <stdio.h>
#include <stdlib.h>

sem_t wrt;
pthread_mutex_t mutex;
int count = 1;
int numReader = 0;

void *writer(void *parameter)
{
      sem_wait(&wrt);
      count *= 2;
      printf("Writer %d modified count to %d\n", (*((int *)parameter)), count);
      sem_post(&wrt);
}

void *reader(void *parameter)
{
      pthread_mutex_lock(&mutex);
      numReader++;
      if (numReader == 1)
            sem_wait(&wrt);

      pthread_mutex_unlock(&mutex);
      printf("reader %d:read count as %d\n", *((*int)parameter), count);

      pthread_mutex_lock(&mutex);
      numReader--;

      if (numReader == 0)
            sem_post(&wrt);

      pthread_mutex_unlock(&mutex);
}

int main()
{
      pthread_t read[3], write[3];
      pthread_mutex_init(&mutex, NULL);
      sem_init(&wrt, 0, 1);
      int a[3] = {1, 2, 3};

      for (int i = 0; i < 3; i++)
            pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);

      for (int i = 0; i < 3; i++)
            pthread_join(read[i], NULL);

      for (int i = 0; i < 3; i++)
            pthread_join(write[i], NULL);

      pthread_mutex_destroy(&mutex);
      sem_destroy(&wrt);

      return 0;
}