#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
};

void calculateTimes(struct Process processes[], int n, int turnaround[], int waiting[], int response[]) {
    int currentTime = 0;
    int remainingTime[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
        response[i] = -1;  // Flag to indicate response time not calculated yet
    }

    int completedProcesses = 0;
    while (completedProcesses < n) {
        int highestPriority = -1;
        int selectedProcess = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0 &&
                (highestPriority == -1 || processes[i].priority < highestPriority)) {
                highestPriority = processes[i].priority;
                selectedProcess = i;
            }
        }

        if (selectedProcess != -1) {
            if (response[selectedProcess] == -1) {
                response[selectedProcess] = currentTime;
            }

            currentTime++;
            remainingTime[selectedProcess]--;

            if (remainingTime[selectedProcess] == 0) {
                turnaround[selectedProcess] = currentTime - processes[selectedProcess].arrivalTime;
                waiting[selectedProcess] = turnaround[selectedProcess] - processes[selectedProcess].burstTime;
                completedProcesses++;
            }
        } else {
            currentTime++;
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
    int n;
    struct Process processes[MAX_PROCESSES];
    int turnaround[MAX_PROCESSES], waiting[MAX_PROCESSES], response[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    calculateTimes(processes, n, turnaround, waiting, response);

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
