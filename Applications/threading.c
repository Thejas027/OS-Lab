#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sm = 0, prod = 1;

void *sum(void *param)
{
      int i, n;
      n = atoi((char *)param); // Cast param to char* and then convert to int
      printf("inside sum thread\n");

      for (i = 0; i < n; i++)
            sm += i;

      printf("\nsum thread completed\n");
      pthread_exit(NULL); // Ensure thread exits properly
}

void *product(void *param)
{
      int i, n;
      n = atoi((char *)param); // Cast param to char* and then convert to int
      printf("\ninside product thread\n");

      for (i = 2; i < n; i++)
            prod *= i;

      printf("\nmultiplication thread completed\n");
      pthread_exit(NULL); // Ensure thread exits properly
}

int main(int argc, char *argv[])
{
      if (argc < 2)
      {
            fprintf(stderr, "Usage: %s <number>\n", argv[0]);
            return 1;
      }

      pthread_t T1, T2;
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      pthread_create(&T1, &attr, sum, (void *)argv[1]);
      pthread_create(&T2, &attr, product, (void *)argv[1]);

      pthread_join(T1, NULL);
      pthread_join(T2, NULL);

      printf("Inside main thread\n");
      printf("sum = %d\n", sm);
      printf("product = %d\n", prod);

      return 0;
}
