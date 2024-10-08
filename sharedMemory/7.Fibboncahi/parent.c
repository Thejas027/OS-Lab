// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <wait.h>

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

//       printf("[PARENT]: Enter n: ");
//       scanf("%d", &shm_ptr->n);

//       pid_t child_pid;

//       if ((child_pid = fork()) == 0)
//       {
//             execlp("./child", "./child", NULL);
//       }
//       else
//       {
//             wait(NULL);
//             printf("[PARENT]: child finished executing.\n");
//             printf("[PARENT]: The Fibonacci series is:\n");
//             for (int i = 0; i < shm_ptr->n; i++)
//                   printf("%d ", shm_ptr->arr[i]);
//             putchar('\n');
//       }

//       shmdt((void *)shm_ptr);
//       shmctl(shmid, IPC_RMID, NULL);
//       printf("[PARENT]: shared memory deleted\n");
//       return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

void main()
{
      int shmid, n;
      int *shared_memory;

      shmid = shmget((key_t)110011, 1024, 0666 | IPC_CREAT);
      shared_memory = (int *)shmat(shmid, NULL, 0);

      printf("Enter n>> ");
      scanf("%d", &n);
      char nstr[20];
      sprintf(nstr, "%d", n);

      if (fork() == 0)
      {
            execlp("./child", "child", nstr, NULL);
      }
      else
      {
            wait(NULL);

            for (int i = 0; i < n; i++)
            {
                  printf("%d ", shared_memory[i]);
            }
            printf("\n");

            shmdt(shared_memory);
      }
}