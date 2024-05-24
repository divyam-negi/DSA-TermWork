#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

int listToNumber(Node* head) {
    int num = 0;
    while (head != NULL) {
        num = num * 10 + head->data;
        head = head->next;
    }
    return num;
}

void numberToList(int num, Node** head) {
    if (num == 0) {
        appendNode(head, 0);
        return;
    }
    while (num > 0) {
        int digit = num % 10;
        appendNode(head, digit);
        num /= 10;
    }
}

Node* subtractLists(Node* list1, Node* list2) {
    int num1 = listToNumber(reverseList(list1));
    int num2 = listToNumber(reverseList(list2));
    int result = num1 - num2;
    Node* resultList = NULL;
    numberToList(result, &resultList);
    return reverseList(resultList);
}

void menu() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int choice, data;
    
    while (1) {
        printf("Menu:\n");
        printf("1. Add node to List 1\n");
        printf("2. Add node to List 2\n");
        printf("3. Display List 1\n");
        printf("4. Display List 2\n");
        printf("5. Subtract Lists and Display Result\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data for List 1: ");
                scanf("%d", &data);
                appendNode(&list1, data);
                break;
            case 2:
                printf("Enter data for List 2: ");
                scanf("%d", &data);
                appendNode(&list2, data);
                break;
            case 3:
                printf("List 1: ");
                printList(list1);
                break;
            case 4:
                printf("List 2: ");
                printList(list2);
                break;
            case 5: ;
                Node* result = subtractLists(list1, list2);
                printf("Result: ");
                printList(result);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
