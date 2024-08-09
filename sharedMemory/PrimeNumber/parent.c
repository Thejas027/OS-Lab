#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

typedef struct
{
      int count;
      int primes[100];
} pack_t;

int main(int argc, char *argv[])
{
      if (argc != 3)
      {
            fprintf(stderr, "[PARENT]: Error: Please provide two arguments: M and N.\n");
            return 1;
      }

      int M = atoi(argv[1]);
      int N = atoi(argv[2]);

      char *shm_name = "prime_shm";
      int shm_size = sizeof(pack_t);

      int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
      ftruncate(shm_fd, shm_size);

      pack_t *shm_ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

      pid_t child_pid;

      if ((child_pid = fork()) == 0)
      {
            execlp("./child", "./child", argv[1], argv[2], NULL);
      }
      else
      {
            wait(NULL);
            printf("[PARENT]: Completed Execution.\n");
            printf("[PARENT]: The prime numbers are: ");

            for (int i = 0; i < shm_ptr->count; i++)
            {
                  printf("%d ", shm_ptr->primes[i]);
            }
            putchar('\n');

            munmap(shm_ptr, shm_size);
            shm_unlink(shm_name);
            printf("[PARENT]: Parent process completed.\n");
      }

      return 0;
}
