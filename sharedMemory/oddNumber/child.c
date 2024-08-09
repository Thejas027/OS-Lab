#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <wait.h>

typedef struct
{
      int n;
      int arr[100];
} pack_t;


int main()
{
      key_t key = 1234;
      int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);

      pack_t *shm_ptr = (pack_t)shmat(shmid, NULL, 0);

      printf("[CHILD]: attached shared memory with key = %d , id = %d , address = %d", key, shmid, shm_ptr);

      for (int i = 0; i < shm_ptr->n; i++)
            shm_ptr->arr[i] = 2 * i + 1;

      printf("[Child] ; Finished generating first %d odd numbers\n", shm_ptr->n);

      shmdt((void *)shm_ptr);
      return 0;
}
