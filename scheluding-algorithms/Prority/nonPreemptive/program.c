#include <stdio.h>
#include <limits.h>

typedef struct Process
{
      int pId;
      int arrivalTime, burstTime, completionTime, responseTime, waitingTime, priority, turnAroundTime;
} process;

void priority(process p[], int n)
{
      int totalTurnAroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;
      float avgWaitingTime = 0, avgTurnAroundTime = 0, avgResponseTime = 0;
      int elapsedTime = 0;

      // Sort processes by priority (lower value means higher priority)
      for (int i = 0; i < n - 1; i++)
      {
            for (int j = i + 1; j < n; j++)
            {
                  if (p[i].priority > p[j].priority)
                  {
                        process temp = p[i];
                        p[i] = p[j];
                        p[j] = temp;
                  }
            }
      }

      printf("\nGnat Chart\n");

      for (int i = 0; i < n; i++)
      {
            if (p[i].arrivalTime > elapsedTime)
            {
                  printf("(%d) -- (%d) Idle", elapsedTime, p[i].arrivalTime);
                  elapsedTime = p[i].arrivalTime;
            }

            p[i].responseTime = elapsedTime - p[i].arrivalTime;
            p[i].completionTime = elapsedTime + p[i].burstTime;
            p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
            p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;

            totalResponseTime += p[i].responseTime;
            totalTurnAroundTime += p[i].turnAroundTime;
            totalWaitingTime += p[i].waitingTime;

            // Print Gnat Chart
            printf(" (%d) Process %d (%d) ", elapsedTime, p[i].pId, p[i].completionTime);
            elapsedTime += p[i].burstTime;
      }

      // Calculate averages
      avgResponseTime = (float)totalResponseTime / n;
      avgTurnAroundTime = (float)totalTurnAroundTime / n;
      avgWaitingTime = (float)totalWaitingTime / n;

      // Print averages
      printf("\n\nAverage Waiting Time: %.2f", avgWaitingTime);
      printf("\nAverage Turn Around Time: %.2f", avgTurnAroundTime);
      printf("\nAverage Response Time: %.2f\n", avgResponseTime);
}

void getInput(process p[], int *n)
{
      for (int i = 0; i < *n; i++)
      {
            printf("Enter the arrival time, burst time, and priority of process %d: ", i + 1);
            scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
            p[i].pId = i + 1;
      }
}

int main()
{
      int n;

      printf("Enter the number of processes: ");
      scanf("%d", &n);

      process p[n]; // Use dynamic array size
      getInput(p, &n);
      priority(p, n);

      return 0;
}
