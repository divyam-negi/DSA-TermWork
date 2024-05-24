#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Function to merge two subarrays of arr[].
void merge(char arr[][MAX_LENGTH], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    char L[n1][MAX_LENGTH], R[n2][MAX_LENGTH];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        strcpy(L[i], arr[l + i]);
    for (j = 0; j < n2; j++)
        strcpy(R[j], arr[m + 1 + j]);

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(arr[k], L[i]);
            i++;
        } else {
            strcpy(arr[k], R[j]);
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        strcpy(arr[k], L[i]);
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        strcpy(arr[k], R[j]);
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergeSort(char arr[][MAX_LENGTH], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Function to print the array of strings
void printArray(char arr[][MAX_LENGTH], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

// Function to handle user menu
void menu() {
    char strings[MAX_STRINGS][MAX_LENGTH];
    int n = 0;
    int choice;
    char temp[MAX_LENGTH];

    do {
        printf("\nMenu:\n");
        printf("1. Add a string\n");
        printf("2. Sort strings\n");
        printf("3. Display strings\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                if (n < MAX_STRINGS) {
                    printf("Enter a string: ");
                    fgets(temp, MAX_LENGTH, stdin);
                    temp[strcspn(temp, "\n")] = 0; // Remove trailing newline character
                    strcpy(strings[n], temp);
                    n++;
                } else {
                    printf("Maximum number of strings reached.\n");
                }
                break;
            case 2:
                if (n > 1) {
                    mergeSort(strings, 0, n - 1);
                    printf("Strings sorted successfully.\n");
                } else {
                    printf("Not enough strings to sort.\n");
                }
                break;
            case 3:
                if (n > 0) {
                    printf("The strings are:\n");
                    printArray(strings, n);
                } else {
                    printf("No strings to display.\n");
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;
}
