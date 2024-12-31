#include <stdio.h>
#include <limits.h>

struct Process 
{
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void calculate_waiting_time(struct Process processes[], int process_number) 
{
    processes[0].waiting_time = 0;
    for (int i = 1; i < process_number; i++) 
    {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void calculate_turnaround_time(struct Process processes[], int process_number) 
{
    for (int i = 0; i < process_number; i++) 
    {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void sort_processes_burst_time(struct Process processes[], int process_number) 
{
    for (int i = 0; i < process_number - 1; i++) 
    {
        for (int j = i + 1; j < process_number; j++) 
        {
            if (processes[i].burst_time > processes[j].burst_time) 
            {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void sjf(struct Process processes[], int process_number) 
{
    sort_processes_burst_time(processes, process_number);
    calculate_waiting_time(processes, process_number);
    calculate_turnaround_time(processes, process_number);
    
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("\nSJF Scheduling:\n");
    printf("Process\t\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");


    for (int i = 0; i < process_number; i++) 
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("P%d\t\t\t%d\t\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
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
        printf("Enter burst time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
    }
    sjf(processes, process_number);

    return 0;
}
