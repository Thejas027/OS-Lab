#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct
{
      int n;
      int arr[100];
} pack_t;

int main()
{

      char *name = "fib_shm";
      int size = sizeof(pack_t);

      int shm_fd = shm_open(name, O_RDWR, 0666);

      pack_t *shm_ptr = mmap(0, size, PORT_READ | PORT_WRITE, SHARED_MEMORY, shm_fd, 0);

      int n = shm_ptr->n;

      if (n > 0)
            shm_ptr->arr[0] = 0;

      if (n > 1)
            shm_ptr->arr[1] = 1;

      for (int i = 0; i < shm_ptr->n; i++)
            shm_ptr->arr[i] = shm_ptr->arr[i - 1] + shm_ptr->arr[i - 2];

      munmap(shm_ptr, size);

      return 0;
}