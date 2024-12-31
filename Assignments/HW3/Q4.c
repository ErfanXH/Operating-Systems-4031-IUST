#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100
#define Quantum_Q1 8
#define Quantum_Q2 16

struct process
{
    int pid;     // process id
    int burst;   // burst time
    int arrival; // arrival time
    int wait;    // waiting time
    int done;    // done time
};

typedef struct
{
    struct process *items[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *q)
{
    q->front = -1;
    q->rear = 0;
}

bool isEmpty(Queue *q) { return (q->front == q->rear - 1); }

bool isFull(Queue *q) { return (q->rear == MAX_SIZE); }

void enqueue(Queue *q, struct process *value)
{
    if (isFull(q))
        return;

    q->items[q->rear] = value;
    q->rear++;
}

void dequeue(Queue *q)
{
    if (isEmpty(q))
        return;
    q->front++;
}

int peek(Queue *q)
{
    if (isEmpty(q))
        return -1;

    return q->items[q->front + 1];
}

void printQueue(Queue *q)
{
    if (isEmpty(q))
        return;

    printf("Current Queue: ");
    for (int i = q->front + 1; i < q->rear; i++)
    {
        printf("%d\t", q->items[i]->pid);
    }
    printf("\n");
}

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
        processes[i].done = 0;
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        total_burst += processes[i].burst;
    }

    // sort processes by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival > processes[j + 1].arrival)
            {
                struct process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    Queue q1, q2, q3;
    initializeQueue(&q1); // highest priority
    initializeQueue(&q2); // medium priority
    initializeQueue(&q3); // lowest priority

    for (int i = 0; i < n; i++)
        enqueue(&q1, &processes[i]);

    int i_q1 = -1;
    int p_q2 = -1, i_q2 = -1;
    int p_q3 = -1, i_q3 = -1;

    // scheduling
    for (int i = 0; i < total_burst; i++)
    {
        if (!isEmpty(&q1) && q1.items[q1.front + 1]->arrival <= i)
        {
            printf("Process %d is running in queue 1 at %d.\n", q1.items[q1.front + 1]->pid, i);
            i_q1 = i;

            struct process *p = q1.items[q1.front + 1];
            if (p->burst > Quantum_Q1)
            {
                p->burst -= Quantum_Q1;
                i += Quantum_Q1 - 1;
                for (int j = 0; j < n; j++)
                {
                    if (processes[j].pid != p->pid && processes[j].arrival <= i)
                        processes[j].wait += Quantum_Q1;
                }
                dequeue(&q1);
                enqueue(&q2, p);
            }
            else
            {
                i += p->burst - 1;
                dequeue(&q1);
            }
        }
        else if (!isEmpty(&q2))
        {
            if (q2.items[q2.front + 1]->pid != p_q2 || (q2.items[q2.front + 1]->pid == p_q2 && i - i_q2 > 1))
                printf("Process %d is running in queue 2 at %d.\n", q2.items[q2.front + 1]->pid, i);

            struct process *p = q2.items[q2.front + 1];
            p_q2 = p->pid;
            i_q2 = i;

            p->done++;
            p->burst--;

            if (p->burst == 0)
            {
                p->done = 0;
                dequeue(&q2);
            }
            else if (p->done == Quantum_Q2)
            {
                p->done = 0;
                dequeue(&q2);
                enqueue(&q3, p);
            }
        }
        else if (!isEmpty(&q3))
        {
            if (q3.items[q3.front + 1]->pid != p_q3 || (q3.items[q3.front + 1]->pid == p_q3 && i - i_q3 > 1))
                printf("Process %d is running in queue 3 at %d.\n", q3.items[q3.front + 1]->pid, i);

            struct process *p = q3.items[q3.front + 1];
            p_q3 = p->pid;
            i_q3 = i;

            p->done++;
            p->burst--;

            if (p->burst == 0)
            {
                p->done = 0;
                dequeue(&q2);
            }
        }
    }

    free(processes);

    return 0;
}