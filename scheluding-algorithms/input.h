
#ifndef INPUT_H
#define INPUT_H

#include "process.h"

void getInput(Process p[], int *n);
void fcfs(Process p[], int n);
void sjf(Process p[], int n);
void sjfPreemptive(Process p[], int n);
#endif
