#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
void insertEnd(Node** head, int data);
void displayList(Node* head);
void rearrangeList(Node** head);
void freeList(Node* head);
void menu();

int main() {
    menu();
    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


void displayList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Rearrange the linked list as L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 ...
void rearrangeList(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    // Find the middle of the list
    Node* slow = *head;
    Node* fast = *head;
    while (fast != NULL && fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* second = slow->next;
    slow->next = NULL;

    Node* prev = NULL;
    Node* current = second;
    Node* next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    second = prev;
    
    Node* first = *head;
    while (second != NULL) {
        Node* temp1 = first->next;
        Node* temp2 = second->next;

        first->next = second;
        if (temp1 == NULL) {
            break;
        }
        second->next = temp1;

        first = temp1;
        second = temp2;
    }
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void menu() {
    Node* head = NULL;
    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Insert a node at the end\n");
        printf("2. Display the list\n");
        printf("3. Rearrange the list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insertEnd(&head, value);
                break;
            case 2:
                displayList(head);
                break;
            case 3:
                rearrangeList(&head);
                break;
            case 4:
                freeList(head);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}
