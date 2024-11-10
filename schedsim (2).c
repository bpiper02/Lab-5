
#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// Comparison function for Priority scheduling
int compare_priority(const void *a, const void *b) {
    ProcessType *processA = (ProcessType *)a;
    ProcessType *processB = (ProcessType *)b;
    return processA->pri - processB->pri;  // Sorting by priority
}

// Comparison function for Shortest Job First (SJF) scheduling
int compare_burst_time(const void *a, const void *b) {
    ProcessType *processA = (ProcessType *)a;
    ProcessType *processB = (ProcessType *)b;
    return processA->bt - processB->bt;  // Sorting by burst time
}

// Priority Scheduling Implementation
void priority_scheduling(ProcessType plist[], int n) {
    qsort(plist, n, sizeof(ProcessType), compare_priority);  // Sort by priority

    // Apply FCFS scheduling on sorted list
    int wt = 0;  // Waiting time accumulator
    for (int i = 0; i < n; i++) {
        plist[i].wt = wt;  // Assign waiting time to the process
        plist[i].tat = plist[i].wt + plist[i].bt;  // Calculate turnaround time
        wt += plist[i].bt;  // Update waiting time accumulator
    }
}

// Shortest Job First (SJF) Scheduling Implementation
void shortest_job_first(ProcessType plist[], int n) {
    qsort(plist, n, sizeof(ProcessType), compare_burst_time);  // Sort by burst time

    // Apply SJF scheduling
    int wt = 0;  // Waiting time accumulator
    for (int i = 0; i < n; i++) {
        plist[i].wt = wt;  // Assign waiting time to the process
        plist[i].tat = plist[i].wt + plist[i].bt;  // Calculate turnaround time
        wt += plist[i].bt;  // Update waiting time accumulator
    }
}

// Round Robin Scheduling Implementation
void round_robin(ProcessType plist[], int n, int quantum) {
    int *rem_bt = (int *)malloc(n * sizeof(int));  // Array for remaining burst times
    for (int i = 0; i < n; i++)
        rem_bt[i] = plist[i].bt;  // Initialize remaining burst times

    int t = 0;  // Current time
    int processes_completed = 0;  // Track completed processes

    while (processes_completed < n) {
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {  // Process still has remaining burst time
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    plist[i].wt = t - plist[i].bt;
                    rem_bt[i] = 0;
                    processes_completed++;
                }
            }
        }
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        plist[i].tat = plist[i].wt + plist[i].bt;
    }

    free(rem_bt);
}

// Helper function to print process information (for testing/debugging)
void print_processes(ProcessType plist[], int n) {
    printf("PID\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].art, plist[i].pri, plist[i].wt, plist[i].tat);
    }
}

// Main function
int main() {
    int n, quantum;

    // Sample input
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    ProcessType *plist = (ProcessType *)malloc(n * sizeof(ProcessType));

    printf("Enter time quantum for Round Robin scheduling: ");
    scanf("%d", &quantum);

    // Input process details
    for (int i = 0; i < n; i++) {
        plist[i].pid = i + 1;
        printf("Enter burst time and priority for process %d: ", plist[i].pid);
        scanf("%d %d", &plist[i].bt, &plist[i].pri);
        plist[i].art = 0;  // Assuming all processes arrive at time 0
    }

    // Testing each scheduling algorithm
    printf("\nPriority Scheduling\n");
    priority_scheduling(plist, n);
    print_processes(plist, n);

    printf("\nShortest Job First (SJF) Scheduling\n");
    shortest_job_first(plist, n);
    print_processes(plist, n);

    printf("\nRound Robin Scheduling\n");
    round_robin(plist, n, quantum);
    print_processes(plist, n);

    free(plist);
    return 0;
}
