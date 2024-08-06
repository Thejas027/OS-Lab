#include <stdio.h>

int sm = 0, prod = 1;

void *sum(void *param)
{
      int i, n;
      n = atoi(param);
      printf("inside sum thread\n");

      for (int i = 0; i < n; i++)
            sm += i;

      printf("\nsum thread completed\n");
}

void *product(void *param)
{
      int i, n;
      n = atoi(param);
      printf("\ninside product thread\n");

      for (int i = 2; i < n; i++)
            prod = prod * i;

      printf("\nmultiplication thread completed\n");
}

void main(int argc, char *argv[])
{
      pthread_t T1, T2;
      pthread_attr_t attr;
      pthread_attr_init(&attr);
      pthread_creat(&T1, &attr, sum, NULL);
      pthread_creat(&T2, &attr, product, NULL);
      pthread_join(T1, NULL);
      pthread_join(T2, NULL);
      printf("Inside main thread");
      printf("sum=%d\n", sm);
      printf("product=%d\n", prod);
}