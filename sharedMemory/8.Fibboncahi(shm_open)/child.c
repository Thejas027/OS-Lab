// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/mman.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/stat.h>

// typedef struct
// {
//       int n;
//       int arr[100];
// } pack_t;

// int main()
// {

//       char *name = "fib_shm";
//       int size = sizeof(pack_t);

//       int shm_fd = shm_open(name, O_RDWR, 0666);

//       pack_t *shm_ptr = mmap(0, size, PORT_READ | PORT_WRITE, SHARED_MEMORY, shm_fd, 0);

//       int n = shm_ptr->n;

//       if (n > 0)
//             shm_ptr->arr[0] = 0;

//       if (n > 1)
//             shm_ptr->arr[1] = 1;

//       for (int i = 0; i < shm_ptr->n; i++)
//             shm_ptr->arr[i] = shm_ptr->arr[i - 1] + shm_ptr->arr[i - 2];

//       munmap(shm_ptr, size);

//       return 0;
// }

// Include   -lrt -o child   while compiling

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
      int fd, n;
      int buffer[25];
      int *shared_memory;

      fd = shm_open("chandan", O_RDWR, 0666);

      shared_memory = (int *)mmap(NULL, 1024, PROT_WRITE, MAP_SHARED, fd, 0);

      n = atoi(argv[1]);

      buffer[0] = 0;
      buffer[1] = 1;
      for (int i = 2; i < n; i++)
      {
            buffer[i] = buffer[i - 1] + buffer[i - 2];
      }
      for (int i = 0; i < n; i++)
            shared_memory[i] = buffer[i];
}