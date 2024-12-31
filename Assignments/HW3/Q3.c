#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// Process structure
typedef struct
{
    int pid;            // Process ID
    int burst_time;     // Burst time
    int priority;       // Priority
    int remaining_time; // Remaining time
    int waiting_time;   // Waiting time
    int turnaround_time; // Turnaround time
} Process;

// Comparator to sort processes by priority (descending) and then by PID
int compare_processes(const void *first_proc, const void *second_proc)
{
    Process *proc1 = (Process *)first_proc;
    Process *proc2 = (Process *)second_proc;
    
    if (proc1->priority != proc2->priority)
        return proc2->priority - proc1->priority;  // Higher priority first
    return proc1->pid - proc2->pid;  // If priorities are equal, sort by PID
}

// Read input for processes
void input_processes(Process *processes, int process_count)
{
    for (int i = 0; i < process_count; i++)
    {
        processes[i].pid = i + 1;
        printf("Enter burst time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process P%d : ", processes[i].pid);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }
}

// Execute the processes based on priority and time quantum
void execute_processes(Process *processes, int process_count, int time_quantum)
{
    int current_time = 0;
    int remaining_processes = process_count;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    char **process_results = (char **)malloc(process_count * sizeof(char *));
    for (int i = 0; i < process_count; i++)
    {
        process_results[i] = (char *)malloc(100 * sizeof(char));
    }

    printf("\nOrder of execution : \n");

    // Process execution loop
    while (remaining_processes > 0)
    {
        int current_priority = INT_MAX;
        
        // Find the process with the lowest priority that still has remaining time
        for (int i = 0; i < process_count; i++)
        {
            if (processes[i].remaining_time > 0 && processes[i].priority < current_priority)
            {
                current_priority = processes[i].priority;
                break;
            }
        }

        // Execute processes with the current lowest priority
        for (int i = 0; i < process_count; i++)
        {
            if (processes[i].remaining_time > 0 && processes[i].priority == current_priority)
            {
                int exec_time = (processes[i].remaining_time > time_quantum) ? time_quantum : processes[i].remaining_time;
                current_time += exec_time;
                processes[i].remaining_time -= exec_time;

                // If the process finishes, calculate its turnaround and waiting times
                if (processes[i].remaining_time == 0)
                {
                    processes[i].turnaround_time = current_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    remaining_processes--;
                    total_turnaround_time += processes[i].turnaround_time;
                    total_waiting_time += processes[i].waiting_time;

                    snprintf(process_results[process_count - remaining_processes - 1], 100, 
                             "P%-2d\t\t%-12d%-15d%-18d\n", processes[i].pid, processes[i].burst_time, 
                             processes[i].waiting_time, processes[i].turnaround_time);
                }
                printf("P%d ", processes[i].pid);  // Display current process
            }
        }
    }

    // Output results with proper spacing
    printf("\n\nProcess\t   Burst Time\tWaiting Time  Turnaround Time\n");
    for (int i = 0; i < process_count; i++)
    {
        printf("%s", process_results[i]);
    }
    printf("\n");

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / process_count);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / process_count);

    // Free dynamically allocated memory
    for (int i = 0; i < process_count; i++)
    {
        free(process_results[i]);
    }
    free(process_results);
}

// Main function
int main()
{
    int process_count;
    printf("Enter number of processes : ");
    scanf("%d", &process_count);

    Process *processes = (Process *)malloc(process_count * sizeof(Process));

    input_processes(processes, process_count);  // Input process data

    int time_quantum;
    printf("Enter time quantum : ");
    scanf("%d", &time_quantum);

    qsort(processes, process_count, sizeof(Process), compare_processes);  // Sort processes

    execute_processes(processes, process_count, time_quantum);  // Execute processes

    free(processes);  // Free process array
    return 0;
}
