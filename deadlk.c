#include <stdio.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processes, resources;
int maxNeeds[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

int safeSequence[MAX_PROCESSES];

void input() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the Maximum Needs matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &maxNeeds[i][j]);
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Available resources vector:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }
}

int isSafe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int safeCount = 0;

    for (int i = 0; i < processes; i++) {
        if (finish[i] == 0) {
            int j;
            for (j = 0; j < resources; j++) {
                if (maxNeeds[i][j] - allocation[i][j] > work[j]) {
                    break;
                }
            }

            if (j == resources) {
                // Process can finish, update work and set finish flag
                for (int k = 0; k < resources; k++) {
                    work[k] += allocation[i][k];
                }
                finish[i] = 1;

                // Add the process to the safe sequence
                safeSequence[safeCount++] = i;

                // Start checking from the beginning
                i = -1;
            }
        }
    }

    for (int i = 0; i < processes; i++) {
        if (finish[i] == 0) {
            return 0; // System is not in a safe state
        }
    }

    return 1; // System is in a safe state
}

int main() {
    input();

    if (isSafe()) {
        printf("The system is in a safe state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < processes; i++) {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}
 //5, 3   need = 743122600011431 allo = 010200302211002 avail = 332
