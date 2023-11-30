#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
};

void calculateTimes(struct Process processes[], int n, int turnaround[], int waiting[], int response[]) {
    int completionTime[MAX_PROCESSES];

    // Sort processes based on arrival time (using bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate completion time for each process
    int currentTime = processes[0].arrivalTime;
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        completionTime[i] = currentTime + processes[i].burstTime;
        turnaround[i] = completionTime[i] - processes[i].arrivalTime;
        waiting[i] = turnaround[i] - processes[i].burstTime;
        response[i] = waiting[i];
        currentTime = completionTime[i];
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

    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
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

// n = 5 2201233544
