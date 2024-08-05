#include <stdio.h>

typedef struct Process
{
      int pId;
      int arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime, finished, responseTime;
} Process;

void SFJ(Process p[], int n) {}

int main()
{

      int n;
      printf("Enter the number of process : %d ");
      scanf("%d", &n);

      Process p[n];

      for (int i = 0; i < n; i++)
      {
            printf("Enter the arrival time and burst time of the process %d : ");
            scanf("%d %d", &p[i].arrivalTime, p[i].burstTime);

            p[i].pId = i + 1;
            p[i].finished = 0;
      }

      SFJ(p, n);
      return 0;
}