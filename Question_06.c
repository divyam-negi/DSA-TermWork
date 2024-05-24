#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define TIME_SLICE 10 

typedef struct {
    int processID;
    int burstTime;
    int remainingTime;
    int completionTime;
} Process;

typedef struct {
    Process processes[MAX];
    int front;
    int rear;
    int size;
} CircularQueue;

void initializeQueue(CircularQueue* q);
int isFull(CircularQueue* q);
int isEmpty(CircularQueue* q);
void enqueue(CircularQueue* q, Process p);
Process dequeue(CircularQueue* q);
void allocateTimeSlots(CircularQueue* q);
void displayProcesses(CircularQueue* q);
void addProcess(CircularQueue* q);

int main() {
    CircularQueue queue;
    initializeQueue(&queue);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add Process\n");
        printf("2. Allocate Time Slots\n");
        printf("3. Display Processes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addProcess(&queue);
                break;
            case 2:
                allocateTimeSlots(&queue);
                break;
            case 3:
                displayProcesses(&queue);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);

    return 0;
}

void initializeQueue(CircularQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}


int isFull(CircularQueue* q) {
    return q->size == MAX;
}

int isEmpty(CircularQueue* q) {
    return q->size == 0;
}

void enqueue(CircularQueue* q, Process p) {
    if(isFull(q)) {
        printf("Queue is full! Cannot add more processes.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->processes[q->rear] = p;
    q->size++;
}

Process dequeue(CircularQueue* q) {
    Process p = {0, 0, 0, 0};
    if(isEmpty(q)) {
        printf("Queue is empty!\n");
        return p;
    }
    p = q->processes[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return p;
}

void allocateTimeSlots(CircularQueue* q) {
    if(isEmpty(q)) {
        printf("No processes to allocate time slots.\n");
        return;
    }

    int timeElapsed = 0;
    int processCount = q->size;
    while(processCount > 0) {
        Process p = dequeue(q);
        if(p.remainingTime > TIME_SLICE) {
            p.remainingTime -= TIME_SLICE;
            timeElapsed += TIME_SLICE;
            enqueue(q, p);
        } else {
            timeElapsed += p.remainingTime;
            p.completionTime = timeElapsed;
            printf("Process %d completed in %d ns\n", p.processID, p.completionTime);
            processCount--;
        }
    }
}

void displayProcesses(CircularQueue* q) {
    if(isEmpty(q)) {
        printf("No processes to display.\n");
        return;
    }
    printf("Processes in the queue:\n");
    printf("ID\tBurst Time\tRemaining Time\tCompletion Time\n");
    for(int i = 0; i < q->size; i++) {
        int index = (q->front + i) % MAX;
        Process p = q->processes[index];
        printf("%d\t%d\t\t%d\t\t%d\n", p.processID, p.burstTime, p.remainingTime, p.completionTime);
    }
}


void addProcess(CircularQueue* q) {
    if(isFull(q)) {
        printf("Cannot add more processes. Queue is full!\n");
        return;
    }
    Process p;
    printf("Enter process ID: ");
    scanf("%d", &p.processID);
    printf("Enter burst time (in ns): ");
    scanf("%d", &p.burstTime);
    p.remainingTime = p.burstTime;
    p.completionTime = 0;
    enqueue(q, p);
    printf("Process added successfully!\n");
}
