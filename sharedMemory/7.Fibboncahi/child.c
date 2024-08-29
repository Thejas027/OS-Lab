// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/types.h>
// #include <unistd.h>

// typedef struct
// {
//       int n;
//       int arr[100];
// } pack_t;

// int main()
// {
//       key_t key = ftok("shm-file", 65);
//       int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);
//       pack_t *shm_ptr = (pack_t *)shmat(shmid, NULL, 0);

//       int n = shm_ptr->n;
//       if (n > 0)
//       {
//             shm_ptr->arr[0] = 0;
//       }
//       if (n > 1)
//       {
//             shm_ptr->arr[1] = 1;
//       }
//       for (int i = 2; i < n; i++)
//       {
//             shm_ptr->arr[i] = shm_ptr->arr[i - 1] + shm_ptr->arr[i - 2];
//       }

//       shmdt((void *)shm_ptr);
//       return 0;
// }

// Compile this program with arguments -> ( -o child )

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

void main(int argc, char *argv[])
{

      int shmid, n;
      int buffer[25];
      int *shared_memory;
      n = atoi(argv[1]);

      shmid = shmget((key_t)110011, 1024, 0666);
      shared_memory = (int *)shmat(shmid, NULL, 0);

      buffer[0] = 0;
      buffer[1] = 1;
      for (int i = 2; i < n; i++)
      {
            buffer[i] = buffer[i - 1] + buffer[i - 2];
      }

      for (int i = 0; i < n; i++)
            shared_memory[i] = buffer[i];
}