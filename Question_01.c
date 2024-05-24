#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct PriorityQueue {
    Node* front;
    Node* rear;
} PriorityQueue;

void initQueue(PriorityQueue* q) {
    q->front = q->rear = NULL;
}

void insert(PriorityQueue* q, int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->next = newNode->prev = NULL;

    if (q->front == NULL || id < q->front->id) {
        newNode->next = q->front;
        if (q->front != NULL)
            q->front->prev = newNode;
        q->front = newNode;
        if (q->rear == NULL)
            q->rear = newNode;
    } else {
        Node* temp = q->front;
        while (temp->next != NULL && temp->next->id < id)
            temp = temp->next;
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != NULL)
            temp->next->prev = newNode;
        else
            q->rear = newNode;
        temp->next = newNode;
    }
}

void serve(PriorityQueue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    else
        q->front->prev = NULL;
    free(temp);
}

void display(PriorityQueue* q) {
    Node* temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->id);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    PriorityQueue q;
    initQueue(&q);

    int choice, id;

    while (1) {
        printf("1. Insert\n");
        printf("2. Serve\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Element: ");
                scanf("%d", &id);
                insert(&q, id);
                break;
            case 2:
                serve(&q);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}