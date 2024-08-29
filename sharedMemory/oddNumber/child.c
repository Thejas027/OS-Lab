// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/ipc.h>
// #include <sys/types.h>
// #include <sys/shm.h>
// #include <wait.h>

// typedef struct
// {
//       int n;
//       int arr[100];
// } pack_t;

// int main()
// {
//       key_t key = 1234;
//       int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);

//       pack_t *shm_ptr = (pack_t)shmat(shmid, NULL, 0);

//       printf("[CHILD]: attached shared memory with key = %d , id = %d , address = %d", key, shmid, shm_ptr);

//       for (int i = 0; i < shm_ptr->n; i++)
//             shm_ptr->arr[i] = 2 * i + 1;

//       printf("[Child] ; Finished generating first %d odd numbers\n", shm_ptr->n);

//       shmdt((void *)shm_ptr);
//       return 0;
// }

// Include -lrt -o while compiling

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

void main(int argc, char *argv[])
{

      int m = atoi(argv[1]);
      int n = atoi(argv[2]);
      int fd, i, j, flag;
      int *shared_memory;

      fd = shm_open("vss", O_RDWR, 0666);
      shared_memory = (int *)mmap(NULL, 1024, PROT_WRITE, MAP_SHARED, fd, 0);

      int k = 0;
      for (i = m; i <= n; i++)
      {
            flag = 1;
            for (j = 2; j <= i / 2; j++)
            {
                  if (i % j == 0)
                  {
                        flag = 0;
                        break;
                  }
            }
            if (flag)
            {
                  shared_memory[k++] = i;
            }
      }
      shared_memory[k] = 0;
}
