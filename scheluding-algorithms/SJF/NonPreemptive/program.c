#include <stdio.h>
#include <limits.h> // For INT_MAX

typedef struct process
{
      int pid;
      int arrivalTime, burstTime, turnAroundTime, waitingTime, responseTime, finished, completionTime;
} process;

void SFJ(process p[], int n)
{
      int totalTurnAroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;
      int elapsedTime = 0;
      int remainingProcess = n;

      printf("\nGnat Chart\n");

      while (remainingProcess)
      {
            int exec = -1;
            int shortestBurstTime = INT_MAX;

            // Find the process with the shortest burst time
            for (int i = 0; i < n; i++)
            {
                  if (!p[i].finished && p[i].arrivalTime <= elapsedTime)
                  {
                        if (p[i].burstTime < shortestBurstTime)
                        {
                              exec = i;
                              shortestBurstTime = p[i].burstTime;
                        }
                  }
            }

            if (exec == -1)
            {
                  printf("(%d) -- (%d) Idle\n", elapsedTime, elapsedTime + 1);
                  elapsedTime++;
            }
            else
            {
                  // Update times
                  p[exec].responseTime = elapsedTime - p[exec].arrivalTime;
                  elapsedTime += p[exec].burstTime;
                  p[exec].completionTime = elapsedTime;
                  p[exec].turnAroundTime = p[exec].completionTime - p[exec].arrivalTime;
                  p[exec].waitingTime = p[exec].turnAroundTime - p[exec].burstTime;
                  p[exec].finished = 1;
                  remainingProcess--;

                  totalWaitingTime += p[exec].waitingTime;
                  totalTurnAroundTime += p[exec].turnAroundTime;
                  totalResponseTime += p[exec].responseTime;

                  // Print Gnat Chart
                  printf("(%d) Process %d (%d) ", elapsedTime - p[exec].burstTime, p[exec].pid, elapsedTime);
            }
      }

      // Print averages
      printf("\n\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
      printf("\nAverage Turn Around Time: %.2f", (float)totalTurnAroundTime / n);
      printf("\nAverage Response Time: %.2f\n", (float)totalResponseTime / n);
}

void getInput(process p[], int *n)
{
      for (int i = 0; i < *n; i++)
      {
            printf("Enter arrival time and burst time for process %d: ", i + 1);
            scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
            p[i].pid = i + 1;
            p[i].finished = 0;
      }
}

int main()
{
      int n;

      printf("Enter the number of processes: ");
      scanf("%d", &n);

      process p[n];
      getInput(p, &n);
      SFJ(p, n);

      return 0;
}