#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
      pid_t my_pid, child_pid, parent_pid;
      child_pid = fork();

      if (child_pid < 0)
      {
            printf("\n Fork failed,exiting\n");
            exit(1);
      }

      if (child_pid == 0)
      {
            printf("\n[CHILD] this is child process\n");
            my_pid = getpid();
            parent_pid = getppid();
            printf("[CHILD] my pid : %d\n", my_pid);
            printf("[CHILD] my parents pid : %d \n", parent_pid);
            printf("\nExiting [child]\n");
            exit(0);
      }

      else
      {
            printf("This is parents process\n");
            my_pid = getpid();
            parent_pid = getppid();
            printf("[parent] parent pid : %d", my_pid);
            printf("[parent] my parents pid : %d", parent_pid);
            printf("Parent pid is sleeping of 10 seconds\n");
            sleep(10);
            printf("[parent] child process with pid = %d has ended, but still has a entry in the table\n", my_pid);
            printf("[parent] its therefore a zombie process\n");
            wait(NULL);
      }
      return 0;
}