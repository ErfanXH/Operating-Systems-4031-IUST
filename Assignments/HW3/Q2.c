#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;     // process id
    int burst;   // burst time
    int arrival; // arrival time
    int wait;    // waiting time
};

int main()
{
    int n; // number of processes

    scanf("%d", &n);

    struct process *processes = malloc(n * sizeof(struct process)); // list of processes

    int total_burst = 0;
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i;
        processes[i].wait = 0;
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        total_burst += processes[i].burst;
    }

    int under_service = 0;

    for (int i = 0; i < total_burst; i++)
    {
        if (under_service != 0)
        {
            under_service--;
            continue;
        }

        // update waits
        for (int j = 0; j < n; j++)
            if (processes[j].arrival <= i && processes[j].burst > 0)
                processes[j].wait = i - processes[j].arrival;

        // calculate hrrns
        float max_hrrn = -9999999.0;
        int max_process = -1;
        for (int j = 0; j < n; j++)
        {
            if (processes[j].arrival <= i && processes[j].burst > 0)
            {
                float hrrn = 1 + (float)processes[j].wait / (float)processes[j].burst;
                if (hrrn > max_hrrn)
                {
                    max_hrrn = hrrn;
                    max_process = j;
                }
            }
        }
        under_service = processes[max_process].burst - 1;
        processes[max_process].burst = 0;
        // log execution
        printf("process %d is executed at %d\n", max_process, i);
    }
    // average waiting time
    float avg_wait = 0;
    for (int j = 0; j < n; j++)
        avg_wait += processes[j].wait;
    avg_wait /= n;

    printf("average waiting time: %.3f\n", avg_wait);

    free(processes);

    return 0;
}