#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process
{
      int pId;
      int arrivalTime, burstTime, completionTime, waitingTime, responseTime, turnAroundTime, finished;
} Process;

#endif