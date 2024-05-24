#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
void insert(Node** head, int value);
void rearrange(Node** head, int V);
void display(Node* head);
void menu();

int main() {
    Node* head = NULL;
    int choice, value, V;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&head, value);
                break;
            case 2:
                printf("Enter the value V: ");
                scanf("%d", &V);
                rearrange(&head, V);
                break;
            case 3:
                display(head);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

// Function to display the menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Insert value into linked list\n");
    printf("2. Rearrange linked list based on value V\n");
    printf("3. Display linked list\n");
    printf("4. Exit\n");
}

// Function to insert a new node at the end of the list
void insert(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

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

// Function to rearrange the linked list based on value V
void rearrange(Node** head, int V) {
    if (*head == NULL) return;

    Node* lessHead = NULL;
    Node* lessTail = NULL;
    Node* greaterHead = NULL;
    Node* greaterTail = NULL;
    Node* current = *head;

    while (current != NULL) {
        if (current->data < V) {
            if (lessHead == NULL) {
                lessHead = current;
                lessTail = current;
            } else {
                lessTail->next = current;
                lessTail = lessTail->next;
            }
        } else {
            if (greaterHead == NULL) {
                greaterHead = current;
                greaterTail = current;
            } else {
                greaterTail->next = current;
                greaterTail = greaterTail->next;
            }
        }
        current = current->next;
    }

    // Connect the less list to the greater list
    if (lessTail != NULL) {
        lessTail->next = greaterHead;
        *head = lessHead;
    } else {
        *head = greaterHead;
    }

    // Terminate the greater list
    if (greaterTail != NULL) {
        greaterTail->next = NULL;
    }
}

// Function to display the linked list
void display(Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* temp = head;
    printf("Linked list: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
