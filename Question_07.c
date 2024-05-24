#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* findMax(Node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

Node* findSecondMax(Node* root) {
    Node* parent = NULL;
    while (root->right != NULL) {
        parent = root;
        root = root->right;
    }
    if (root->left != NULL) {
        return findMax(root->left);
    }
    return parent;
}

int countLeftOnlyNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    if (root->left != NULL && root->right == NULL) {
        count = 1;
    }
    return count + countLeftOnlyNodes(root->left) + countLeftOnlyNodes(root->right);
}

int countLeafNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int findHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countRightNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countRightNodes(root->right);
}

void menu() {
    Node* root = NULL;
    int choice, value;
    
    do {
        printf("\nMenu:\n");
        printf("1. Insert a node\n");
        printf("2. Search and print the node having second highest value\n");
        printf("3. Count nodes with left child only\n");
        printf("4. Find total number of leaf nodes\n");
        printf("5. Find height of the BST\n");
        printf("6. Count nodes from right-hand side of root node\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2: {
                Node* secondMaxNode = findSecondMax(root);
                if (secondMaxNode != NULL) {
                    printf("Second highest value node: %d\n", secondMaxNode->data);
                } else {
                    printf("Tree does not have enough nodes.\n");
                }
                break;
            }
            case 3:
                printf("Nodes with left child only: %d\n", countLeftOnlyNodes(root));
                break;
            case 4:
                printf("Total number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                printf("Height of the BST: %d\n", findHeight(root));
                break;
            case 6:
                if (root != NULL) {
                    printf("Nodes on right-hand side of root node: %d\n", countRightNodes(root->right));
                } else {
                    printf("Tree is empty.\n");
                }
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
