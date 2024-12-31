#include <stdio.h>
#include <limits.h>

struct Process 
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void calculate_waiting_time(struct Process processes[], int process_number) 
{
    int complete = 0, current_time = 0, min_remaining = INT_MAX;
    int shortest = -1, finish_time;
    int check = 0;

    
    for (int i = 0; i < process_number; i++) 
    {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (complete != process_number) 
    {
        min_remaining = INT_MAX;
        shortest = -1;

        
        for (int j = 0; j < process_number; j++) 
        {
            if ((processes[j].arrival_time <= current_time) && (processes[j].remaining_time < min_remaining) && (processes[j].remaining_time > 0)) 
            {
                min_remaining = processes[j].remaining_time;
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) 
        {
            current_time++;
            continue;
        }
 
        processes[shortest].remaining_time--;

        if (processes[shortest].remaining_time == 0) 
        {
            complete++;
            finish_time = current_time + 1;
            processes[shortest].waiting_time = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;

            if (processes[shortest].waiting_time < 0) 
            {
                processes[shortest].waiting_time = 0;
            }
        }

        current_time++;
    }
}

void calculate_turnaround_time(struct Process processes[], int process_number) 
{
    for (int i = 0; i < process_number; i++) 
    {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void srtf(struct Process processes[], int process_number) 
{
    calculate_waiting_time(processes, process_number);
    calculate_turnaround_time(processes, process_number);

    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("\nSRTF Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tWait Time\tTurnaround Time\n");

    for (int i = 0; i < process_number; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average Wait Time: %.2f\n", total_waiting_time / process_number);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / process_number);
}

int main() 
{
    int process_number;
    printf("Enter number of processes: ");
    scanf("%d", &process_number);

    struct Process processes[process_number];

    for (int i = 0; i < process_number; i++) 
    {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d:\n", processes[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    srtf(processes, process_number);

    return 0;
}
