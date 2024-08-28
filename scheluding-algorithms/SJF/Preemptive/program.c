#include <stdio.h>
#include <limits.h>

typedef struct process
{
      int pid;
      int arrivalTime, burstTime, remainingTime, turnAroundTime, waitingTime, responseTime, finished, completionTime, startTime;
      int firstExecution; // flag to check if the process has started execution
} process;

void SRTF(process p[], int n)
{
      int totalTurnAroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;
      int elapsedTime = 0, completed = 0;
      int shortestRemainingTime;
      int exec = -1;

      printf("\nGnat Chart\n");

      while (completed < n)
      {
            shortestRemainingTime = INT_MAX;
            exec = -1;

            // Find the process with the shortest remaining time
            for (int i = 0; i < n; i++)
            {
                  if (p[i].arrivalTime <= elapsedTime && p[i].remainingTime > 0)
                  {
                        if (p[i].remainingTime < shortestRemainingTime)
                        {
                              shortestRemainingTime = p[i].remainingTime;
                              exec = i;
                        }
                        // If two processes have the same remaining time, choose the one with the earlier arrival time
                        if (p[i].remainingTime == shortestRemainingTime)
                        {
                              if (p[i].arrivalTime < p[exec].arrivalTime)
                                    exec = i;
                        }
                  }
            }

            if (exec == -1)
            {
                  printf("(%d) -- (%d) Idle\n", elapsedTime, elapsedTime + 1);
                  elapsedTime++;
                  continue;
            }

            if (p[exec].firstExecution == 0)
            {
                  p[exec].firstExecution = 1;
                  p[exec].responseTime = elapsedTime - p[exec].arrivalTime;
                  p[exec].startTime = elapsedTime;
            }

            p[exec].remainingTime--;
            elapsedTime++;

            if (p[exec].remainingTime == 0)
            {
                  p[exec].finished = 1;
                  completed++;
                  p[exec].completionTime = elapsedTime;
                  p[exec].turnAroundTime = p[exec].completionTime - p[exec].arrivalTime;
                  p[exec].waitingTime = p[exec].turnAroundTime - p[exec].burstTime;
                  totalWaitingTime += p[exec].waitingTime;
                  totalTurnAroundTime += p[exec].turnAroundTime;
                  totalResponseTime += p[exec].responseTime;

                  // Print Gnat Chart
                  printf("(%d) Process %d (%d)\n", p[exec].startTime, p[exec].pid, elapsedTime);
            }
      }

      printf("\n\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
      printf("\nAverage Turn Around Time: %.2f", (float)totalTurnAroundTime / n);
      printf("\nAverage Response Time: %.2f\n", (float)totalResponseTime / n);
}

int main()
{
      int n;

      printf("Enter the number of processes: ");
      scanf("%d", &n);

      process p[n];

      for (int i = 0; i < n; i++)
      {
            printf("Enter arrival time and burst time for process %d: ", i + 1);
            scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
            p[i].pid = i + 1;
            p[i].remainingTime = p[i].burstTime;
            p[i].finished = 0;
            p[i].firstExecution = 0; // initially, the process has not started execution
      }

      SRTF(p, n);

      return 0;
}