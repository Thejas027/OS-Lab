#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
      int pId, arrivalTime, burstTime, completionTime, waitingTime, turnAroundTime, responseTime, finished;
} process;

void fcfs(process p[], int n)
{
      int elapseTime = 0;
      float averageWaitingTime = 0, averageTurnAroundTime = 0, averageResponseTime = 0;
      int totalTurnAroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;

      for (int i = 0; i < n; i++)
      {
            if (p[i].arrivalTime > elapseTime)
            {
                  printf("(%d) - (%d) idle \n", elapseTime, p[i].arrivalTime);
                  elapseTime = p[i].arrivalTime;
            }

            p[i].responseTime = elapseTime - p[i].arrivalTime;
            elapseTime += p[i].arrivalTime;
            p[i].completionTime = elapseTime;

            p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
            p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;

            totalWaitingTime += p[i].waitingTime;
            totalTurnAroundTime += p[i].turnAroundTime;
            totalResponseTime += p[i].responseTime;

            // printing a Gnat Chart
            printf("(%d) process %d (%d) ", elapseTime - p[i].burstTime, p[i].pId, elapseTime);

            // calculating the average times '

            averageTurnAroundTime = (float)totalTurnAroundTime / n;
            averageWaitingTime = (float)totalWaitingTime / n;
            averageResponseTime = (float)totalResponseTime / n;

            // printing those average times
            printf("\n1.Average Turn Around Time : %f \n2.Average Waiting Time : %f\n3.Average Response Time : %f\n", averageTurnAroundTime, averageWaitingTime, averageResponseTime);
      }
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