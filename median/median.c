#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = NULL;
    int *help_ptr = ptr;
    int input;
    int count = 0;
    int capacity = 10;

    // Initializing numbers array of 10 (trash value)
    ptr = (int *)malloc(capacity*sizeof(int));
    if (ptr == NULL) {
        printf("Error allocating memory for int");
        free(ptr);
        exit(EXIT_FAILURE);
    }

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

    // Printing all the numbers
    for (int i = 0; i < count; i++) {
        printf("%d ", ptr[i]);
    }

    // Printing the median value
    printf("\nthe median number is: %d", ptr[count/2]);

    // Freeing all the memory we have used
    free(ptr);
    free(help_ptr);

    exit(EXIT_SUCCESS);
}