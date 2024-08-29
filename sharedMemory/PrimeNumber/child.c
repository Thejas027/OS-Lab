// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>

// typedef struct
// {
//       int count;
//       int primes[100];
// } pack_t;

// bool is_prime(int num)
// {
//       if (num <= 1)
//             return false;
//       if (num == 2)
//             return true;
//       if (num % 2 == 0)
//             return false;
//       for (int i = 3; i * i <= num; i += 2)
//       {
//             if (num % i == 0)
//                   return false;
//       }
//       return true;
// }

// int main(int argc, char *argv[])
// {
//       if (argc != 3)
//       {
//             fprintf(stderr, "[CHILD]: Error: Missing arguments M and N.\n");
//             return 1;
//       }

//       int M = atoi(argv[1]);
//       int N = atoi(argv[2]);

//       char *shm_name = "prime_shm";
//       int shm_size = sizeof(pack_t);

//       int shm_fd = shm_open(shm_name, O_RDWR, 0666);
//       pack_t *shm_ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

//       shm_ptr->count = 0;

//       for (int i = M; i <= N; i++)
//       {
//             if (is_prime(i))
//             {
//                   shm_ptr->primes[shm_ptr->count] = i;
//                   shm_ptr->count++;
//             }
//       }

//       munmap(shm_ptr, shm_size);

//       return 0;
// }

//Compile this program with arguments -> ( -o child )

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

void main(int argc, char* argv[]){
	int n,i,shmid;
	int *shared_memory;
	
	n = atoi(argv[1]);
	
	shmid = shmget((key_t)110011,1024,0666);
	shared_memory = (int*)shmat(shmid,NULL,0);

	int j=0;
	for(i=1;i<2*n;i++){
		if (i%2!=0){
			shared_memory[j] = i;
			j++;
		}
	}
	
}
