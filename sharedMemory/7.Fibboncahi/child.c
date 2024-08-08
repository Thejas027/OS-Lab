#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
      int n;
      int arr[100];
} pack_t;

int main()
{
      key_t key = ftok("shmfile", 65);
      int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);
      pack_t *shm_ptr = (pack_t *)shmat(shmid, NULL, 0);

      int n = shm_ptr->n;
      if (n > 0)
      {
            shm_ptr->arr[0] = 0;
      }
      if (n > 1)
      {
            shm_ptr->arr[1] = 1;
      }
      for (int i = 2; i < n; i++)
      {
            shm_ptr->arr[i] = shm_ptr->arr[i - 1] + shm_ptr->arr[i - 2];
      }

      shmdt((void *)shm_ptr);
      return 0;
}
