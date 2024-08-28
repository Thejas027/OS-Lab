#include <stdio.h>
#include <stdlib.h>

typedef struct
{
      int pId, arrivalTime, burstTime, completionTime, waitingTime, turnAroundTime, responseTime, finished;
} process;

void fcfs(process p[], int n)
{
      int elapseTime = 0;
      int totalTurnAroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;

      for (int i = 0; i < n; i++)
      {
            if (p[i].arrivalTime > elapseTime)
            {
                  printf("(%d) - (%d) idle \n", elapseTime, p[i].arrivalTime);
                  elapseTime = p[i].arrivalTime;
            }

            p[i].responseTime = elapseTime - p[i].arrivalTime;
            elapseTime += p[i].burstTime;
            p[i].completionTime = elapseTime;

            p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
            p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;

            totalWaitingTime += p[i].waitingTime;
            totalTurnAroundTime += p[i].turnAroundTime;
            totalResponseTime += p[i].responseTime;

            // printing a Gnat Chart
            printf("(%d) process %d (%d) ", elapseTime - p[i].burstTime, p[i].pId, elapseTime);
      }
      // calculating the average times '

      printf("\n1.Average Turn Around Time : %f \n2.Average Waiting Time : %f\n3.Average Response Time : %f\n", (float)totalTurnAroundTime / n, (float)totalWaitingTime / n, (float)totalResponseTime / n);
}

void getInput(process p[], int *n)
{

      for (int i = 0; i < *n; i++)
      {
            printf("Enter the arrival time and burst time of the process  %d : ", i + 1);
            scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
            p[i].pId = i + 1;
            p[i].finished = 0;
      }
}

void main()
{
      int n;
      printf("Enter the number of Process : ");
      scanf("%d", &n);

      process p[n];
      getInput(p, &n);
      fcfs(p, n);
}