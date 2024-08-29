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
//       key_t key = 1234;
//       int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);

//       pack_t *shm_ptr = (pack_t *)shmat(shmid, NULL, 0);
//       printf("[PARENT] : created shared memory with key = %d , id = %d, address = %d\n", key, shmid, shm_ptr);

//       printf("[PARENT] : Enter n : ");
//       scanf("%d", shm_ptr->n);

//       pid_t child_pid;

//       if ((child_pid = fork()) == 0)
//             execlp("./child", "./child", NULL);

//       // printing part of the odd number of given first n numbers
//       else
//       {
//             wait(NULL);
//             printf("[PARENT]: child finished executing.\n");
//             printf("[Parent]; The first n odd number are , \n");
//             for (int i = 0; i < shm_ptr->n; i++)
//                   printf("%d", shm_ptr->arr[i]);
//             putchar("\n");
//       }

//       // deleting of created shared memory
//       shmdt((void *)shm_ptr);
//       shmctl(shmid, IPC_RMID, NULL);
//       printf("[PARENT]: shared memory deleted\n");
//       return 0;
// }

// Include -lrt while compiling

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

void main(int argc, char *argv[])
{

      if (argc < 2)
      {
            printf("Didn't pass range\n");
            exit(0);
      }

      int fd, i, j, flag;
      int *shared_memory;

      fd = shm_open("vss", O_CREAT | O_RDWR, 0666);
      ftruncate(fd, 1024);
      shared_memory = (int *)mmap(NULL, 1024, PROT_WRITE, MAP_SHARED, fd, 0);

      if (fork() == 0)
      {
            execlp("./child", "child", argv[1], argv[2], NULL);
      }
      else
      {
            wait(NULL);
            int i = 0;
            while (shared_memory[i] != 0)
            {
                  printf("%d ", shared_memory[i++]);
            }
            printf("\n");
            shm_unlink("vss");
      }
}