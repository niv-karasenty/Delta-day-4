/*
 * General program: inputing numbers until another letter is typed using a while loop then if the count is bigger then the memory we have allocated
 * we reallocate the memory with 2 times the space, then we sort the array using bubble sort and print it sorted and it's median
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Sorting an array
void bubble_sort(int *ptr, int count) {
    int temp;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (ptr[j] > ptr[j+1]) {
                temp = ptr[j];
                ptr[j] = ptr[j+1];
                ptr[j+1] = temp;
            }
        }
    }
}

// Printing all the array
void print_all(int *ptr, int count) {
    if (count == 0) {
        printf("No numbers inserted\n");
    }
    else {
        bubble_sort(ptr, count);
        // Printing all the numbers
        for (int i = 0; i < count; i++) {
            printf("%d ", ptr[i]);
        }
        // Printing the median value
        printf("\nthe median number is: %d", ptr[count/2]);
    }
}

int input_from_user(int *ptr, int capacity) {
    int input;
    int *help_ptr = ptr;
    int count = 0;

    printf("write some numbers: ");
    // Trying to take another input everytime
    while (scanf("%d ", &input) == 1) {
        // If the capacity is full we double it
        if (count == capacity) {
            capacity *= 2;
            // Trying to add more space to the pointers using realloc,
            // I have to say that for this part I have used Google because I am not verry familiar with realloc
            help_ptr = (int *)realloc(ptr, capacity*sizeof(int));
            if (help_ptr == NULL) {
                printf("Error allocating memory for int");
                free(ptr);
                exit(EXIT_FAILURE);
            }
            ptr = help_ptr;
        }
        ptr[count] = input;
        count++;
    }

    return count;
}

int main() {
    int *ptr = NULL;
    int capacity = 10, count;

    // Initializing numbers array of 10 (trash value)
    ptr = (int *)calloc(capacity, sizeof(int));
    if (ptr == NULL) {
        printf("Error allocating memory for int");
        free(ptr);
        exit(EXIT_FAILURE);
    }

    count = input_from_user(ptr, capacity);
    print_all(ptr, count);

    // Freeing all the memory we have used
    free(ptr);

    exit(EXIT_SUCCESS);
}