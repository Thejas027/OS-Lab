#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Process
{
      int pId;
      int arrivalTime, burstTime, completionTime, responseTime, waitingTime, priority, turnAroundTime;
      int reamingTime;
} process;

void priorityPreemptive(process p[], int n)
{
      int totalTurnAroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;
      float avgWaitingTime = 0, avgTurnAroundTime = 0, avgResponseTime = 0;
      int elapsedTime = 0;
      int completedProcess = 0; // Initialize completedProcess
      bool processCompleted[n];
      
      for (int i = 0; i < n; i++)
      {
            processCompleted[i] = false;
            p[i].reamingTime = p[i].burstTime;
      }

      while (completedProcess < n)
      {
            int idx = -1;
            int highestPriority = INT_MAX;

            for (int i = 0; i < n; i++)
            {
                  if (!processCompleted[i] && p[i].arrivalTime <= elapsedTime && p[i].priority < highestPriority)
                  {
                        idx = i;
                        highestPriority = p[i].priority;
                  }
            }

            if (idx == -1)
            {
                  printf("(%d) -- (%d) idle\n", elapsedTime, elapsedTime + 1);
                  elapsedTime++;
                  continue;
            }

            if (p[idx].reamingTime == p[idx].burstTime)
                  p[idx].responseTime = elapsedTime - p[idx].arrivalTime;

            p[idx].reamingTime--;
            elapsedTime++;

            if (p[idx].reamingTime == 0)
            {
                  processCompleted[idx] = true;
                  completedProcess++; // Increment completedProcess

                  p[idx].completionTime = elapsedTime;
                  p[idx].turnAroundTime = p[idx].completionTime - p[idx].arrivalTime;
                  p[idx].waitingTime = p[idx].turnAroundTime - p[idx].burstTime;

                  totalWaitingTime += p[idx].waitingTime;
                  totalTurnAroundTime += p[idx].turnAroundTime;
                  totalResponseTime += p[idx].responseTime;

                  // Printing the Gantt chart
                  printf(" (%d) process %d (%d) ", elapsedTime - p[idx].burstTime, p[idx].pId, elapsedTime);
            }
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
            printf("Enter arrival time, burst time and priority of process %d: ", i + 1);
            scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
            p[i].pId = i + 1;
      }
}

int main()
{
      int n;
      printf("Enter the number of processes: ");
      scanf("%d", &n);

      process p[n];
      getInput(p, &n);
      priorityPreemptive(p, n);
      return 0;
}
