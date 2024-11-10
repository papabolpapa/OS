#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[n], burst_time[n], remaining_time[n], completion_time[n];
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;
    int smallest, time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    printf("\nGantt Chart (Process execution sequence):\n");

    while (completed != n) {
        smallest = -1;
        int min_remaining_time = 9999;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] > 0 && remaining_time[i] < min_remaining_time) {
                min_remaining_time = remaining_time[i];
                smallest = i;
            }
        }

        if (smallest == -1) {
            time++;
            continue;
        }

        remaining_time[smallest]--;
        printf("P%d ", smallest + 1);

        if (remaining_time[smallest] == 0) {
            completed++;
            completion_time[smallest] = time + 1;
            turnaround_time[smallest] = completion_time[smallest] - arrival_time[smallest];
            waiting_time[smallest] = turnaround_time[smallest] - burst_time[smallest];
            total_waiting_time += waiting_time[smallest];
            total_turnaround_time += turnaround_time[smallest];
        }

        time++;
    }

    printf("\n\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}



#include <stdio.h>

int main() {
    int n, time_quantum, time = 0, completed = 0, total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int arrival_time[n], burst_time[n], remaining_time[n], waiting_time[n], turnaround_time[n], completion_time[n];

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    printf("\nGantt Chart (Process execution sequence):\n");
    while (completed < n) {
        int process_executed = 0;
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] > 0) {
                process_executed = 1;
                printf("P%d ", i + 1);
                if (remaining_time[i] > time_quantum) {
                    time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    time += remaining_time[i];
                    completion_time[i] = time;
                    turnaround_time[i] = time - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                    total_waiting_time += waiting_time[i];
                    total_turnaround_time += turnaround_time[i];
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }
        if (!process_executed) time++;
    }

    printf("\n\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}