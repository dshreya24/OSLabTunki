#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
};

void calculateTimes(struct Process processes[], int n, int turnaround[], int waiting[], int response[], int quantumTime) {
    int remainingTime[MAX_PROCESSES];
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
        response[i] = -1;  // Flag to indicate response time not calculated yet
    }

    int completedProcesses = 0;
    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && processes[i].arrivalTime <= currentTime) {
                if (response[i] == -1) {
                    response[i] = currentTime;
                }

                if (remainingTime[i] > quantumTime) {
                    currentTime += quantumTime;
                    remainingTime[i] -= quantumTime;
                } else {
                    currentTime += remainingTime[i];
                    turnaround[i] = currentTime - processes[i].arrivalTime;
                    waiting[i] = turnaround[i] - processes[i].burstTime;
                    remainingTime[i] = 0;
                    completedProcesses++;
                }
            }
        }
    }
}

void calculateAverages(int times[], int n, float *average) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += times[i];
    }
    *average = (float)sum / n;
}

void displayResults(struct Process processes[], int n, int turnaround[], int waiting[], int response[]) {
    printf("\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\tResponse Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].processID, processes[i].arrivalTime, processes[i].burstTime,
               turnaround[i], waiting[i], response[i]);
    }
}

int main() {
    int n, quantumTime;
    struct Process processes[MAX_PROCESSES];
    int turnaround[MAX_PROCESSES], waiting[MAX_PROCESSES], response[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    printf("Enter the quantum time: ");
    scanf("%d", &quantumTime);

    calculateTimes(processes, n, turnaround, waiting, response, quantumTime);

    displayResults(processes, n, turnaround, waiting, response);

    float avgTurnaround, avgWaiting, avgResponse;
    calculateAverages(turnaround, n, &avgTurnaround);
    calculateAverages(waiting, n, &avgWaiting);
    calculateAverages(response, n, &avgResponse);

    printf("\nAverage Turnaround Time: %.2f", avgTurnaround);
    printf("\nAverage Waiting Time: %.2f", avgWaiting);
    printf("\nAverage Response Time: %.2f\n", avgResponse);

    return 0;
}

// n = 5 0852176385
