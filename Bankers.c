#include <stdio.h>

int main() {
    int n, r;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &r);

    int alloc[n][r]; // Allocation matrix
    int max[n][r];   // Maximum demand matrix
    int avail[r];    // Available resources
    int need[n][r];  // Need matrix
    int i,j;
    // Input Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++){
        printf("\nEnter Allocation for process P%d : ",i);
        for (int j = 0; j < r; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    // Input Maximum Matrix
    printf("\nEnter the Maximum Matrix:\n");
    for (int i = 0; i < n; i++){
        printf("\nEnter Maximum_Need for process P%d : ",i);
        for (int j = 0; j < r; j++){
            scanf("%d", &max[i][j]);
        }
    }
    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < r; i++){
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix as (Need = Max - Allocation)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < r; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    int finished[n];     // Tracks if processes are completed
    int safeSequence[n]; // Stores the safe sequence
    for (int i = 0; i < n; i++)
        finished[i] = 0; // Initialize all processes as unfinished

    int count = 0; // For safe sequence index

    // Find Safe Sequence
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) { // If process is not finished
                int canProceed = 1;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) { // Check if needs are met
                        canProceed = 0;
                        break;
                    }
                }
                if (canProceed) {
                    // Process can proceed, add to safe sequence
                    safeSequence[count++] = i;
                    for (int j = 0; j < r; j++)
                        avail[j] += alloc[i][j]; // Release resources
                    finished[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) { // If no process could proceed
            printf("\nThe system is in an UNSAFE state.\n");
            return 1;
        }
    }

    // Safe sequence found
    printf("\nThe system is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return 0;
}