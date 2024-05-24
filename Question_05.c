#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node
typedef struct Node {
    int coefficient;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coefficient) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coefficient = coefficient;
    newNode->next = NULL;
    return newNode;
}

// Function to create a linked list representing a quadratic equation
Node* createQuadraticEquation() {
    int coeff;
    Node* head = NULL;
    Node* temp = NULL;

    printf("Enter coefficient for x^2: ");
    scanf("%d", &coeff);
    head = createNode(coeff);

    printf("Enter coefficient for x: ");
    scanf("%d", &coeff);
    head->next = createNode(coeff);

    printf("Enter constant term: ");
    scanf("%d", &coeff);
    head->next->next = createNode(coeff);

    return head;
}

// Function to display a quadratic equation
void displayQuadraticEquation(Node* head) {
    if (head == NULL) {
        printf("Equation is empty.\n");
        return;
    }
    printf("%dx^2 + %dx + %d\n", head->coefficient, head->next->coefficient, head->next->next->coefficient);
}

// Function to add two quadratic equations
Node* addQuadraticEquations(Node* eq1, Node* eq2) {
    if (eq1 == NULL || eq2 == NULL) {
        return NULL;
    }
    Node* result = createNode(eq1->coefficient + eq2->coefficient);
    result->next = createNode(eq1->next->coefficient + eq2->next->coefficient);
    result->next->next = createNode(eq1->next->next->coefficient + eq2->next->next->coefficient);

    return result;
}

// Function to free the linked list
void freeLinkedList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Main function with menu-driven interface
int main() {
    Node* eq1 = NULL;
    Node* eq2 = NULL;
    Node* result = NULL;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create first quadratic equation\n");
        printf("2. Create second quadratic equation\n");
        printf("3. Display first quadratic equation\n");
        printf("4. Display second quadratic equation\n");
        printf("5. Add the two quadratic equations\n");
        printf("6. Display the result of addition\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (eq1 != NULL) freeLinkedList(eq1);
                printf("Creating first quadratic equation:\n");
                eq1 = createQuadraticEquation();
                break;
            case 2:
                if (eq2 != NULL) freeLinkedList(eq2);
                printf("Creating second quadratic equation:\n");
                eq2 = createQuadraticEquation();
                break;
            case 3:
                printf("First quadratic equation is: ");
                displayQuadraticEquation(eq1);
                break;
            case 4:
                printf("Second quadratic equation is: ");
                displayQuadraticEquation(eq2);
                break;
            case 5:
                if (result != NULL) freeLinkedList(result);
                result = addQuadraticEquations(eq1, eq2);
                printf("The quadratic equations have been added.\n");
                break;
            case 6:
                printf("The result of the addition is: ");
                displayQuadraticEquation(result);
                break;
            case 7:
                freeLinkedList(eq1);
                freeLinkedList(eq2);
                freeLinkedList(result);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
