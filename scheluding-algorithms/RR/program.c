#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
      int id, arrivalTime, burstTime, completionTime, responseTime, totalTurnAroundTime, waitingTime, remainingTime, flag;
} Process;

void roundRobin(Process p[], int n, int quantum)
{
      int totalTurnAroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;
      int completed = 0, elapsedTime = p[0].arrivalTime;

      int waitQueue[100], front = 0, rear = 0;
      waitQueue[rear++] = 0;
      p[0].flag = 1;

      printf("\nGnat Chart:\n");
      while (completed < n)
      {
            int i = waitQueue[front++];

            if (p[i].remainingTime == p[i].burstTime)
                  p[i].responseTime = elapsedTime - p[i].arrivalTime;

            if (p[i].remainingTime > quantum)
            {
                  p[i].remainingTime -= quantum;
                  elapsedTime += quantum;
                  printf("| (%d) P%d (%d) ", elapsedTime - quantum, p[i].id, elapsedTime);
            }
            else
            {
                  completed++;
                  elapsedTime += p[i].remainingTime;
                  printf("| (%d) P%d (%d) ", elapsedTime - p[i].remainingTime, p[i].id, elapsedTime);
                  p[i].remainingTime = 0;
                  p[i].completionTime = elapsedTime;
                  p[i].totalTurnAroundTime = p[i].completionTime - p[i].arrivalTime;
                  p[i].waitingTime = p[i].totalTurnAroundTime - p[i].burstTime;

                  totalResponseTime += p[i].responseTime;
                  totalTurnAroundTime += p[i].totalTurnAroundTime;
                  totalWaitingTime += p[i].waitingTime;
            }

            for (int i = 0; i < n && p[i].arrivalTime <= elapsedTime; i++)
            {
                  if (p[i].flag == 0 && p[i].remainingTime > 0)
                  {
                        waitQueue[rear++] = i;
                        p[i].flag = 1;
                  }
            }

            if (p[i].remainingTime > 0)
                  waitQueue[rear++] = i;
      }

      printf("\n");
      printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");
      for (int i = 0; i < n; i++)
      {
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].totalTurnAroundTime, p[i].waitingTime, p[i].responseTime);
      }

      printf("Average TAT = %.2f\nAverage WT = %.2f\nAverage RT = %.2f\n", (float)totalTurnAroundTime / n, (float)totalWaitingTime / n, (float)totalResponseTime / n);
}

int main()
{
      int n, quantum;
      printf("Enter the number of processes: ");
      scanf("%d", &n);
      Process p[n];

      for (int i = 0; i < n; i++)
      {
            printf("Process %d\n", i + 1);
            printf("Enter Arrival Time & Burst Time: ");
            scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
            p[i].id = i + 1;
            p[i].remainingTime = p[i].burstTime;
            p[i].flag = 0;
            printf("\n");
      }

      printf("Enter the time quantum: ");
      scanf("%d", &quantum);

      // Sort processes based on arrival time
      for (int i = 0; i < n - 1; i++)
      {
            for (int j = 0; j < n - i - 1; j++)
            {
                  if (p[j].arrivalTime > p[j + 1].arrivalTime)
                  {
                        Process temp = p[j];
                        p[j] = p[j + 1];
                        p[j + 1] = temp;
                  }
            }
      }

      roundRobin(p, n, quantum);
      return 0;
}
