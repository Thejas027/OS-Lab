#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

typedef struct
{
      int n;
      int arr[100];
} pack_t;

int main()
{
      char *name = "fib_shm";
      int size = sizeof(pack_t);

      int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
      ftruncate(shm_fd, size);

      pack_t *shm_ptr = mmap(0, size, PORT_READ | PORT_WRITE, MAP_SHARED, shm_fd, 0);

      printf("[PARENT]:Enter n :");
      scanf("%d", &shm_ptr->n);

      pid_t child_pid;

      if ((child_pid == fork()) == 0)
            execlp("./child", "./child", NULL);

      else
      {
            wait(NULL);
            printf("[PARENT] completed Execution.\n");
            printf("{PARENT} : The fib series si : ");

            for (int i = 0; i < shm_ptr->n; i++)
                  printf("%d", shm_ptr->arr[i]);
            putchar("\n");
      }

      munmap(shm_ptr, size);
      shm_unlink(name);
      printf("{parent}: parent process completed.\n");
      return 0;
}