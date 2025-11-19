#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* remove_dup_1(int *size, int *arr, int array_size) {
    // Trying to allocate new memory the size of the array
    int *new_array = (int *)malloc(array_size * sizeof(int));
    if (new_array == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    // Copying the values of the array to the new array
    memcpy(new_array, arr, array_size * sizeof(int));

    // inserting the size to the size pointer
    *size = array_size;

    return new_array;
}

// Using the pointer to the address, changing its address and thus changing where the new array starts while allocating new memory and copying the old array
int remove_dup_2(int **addr, int *arr, int array_size) {
    // Allocating new memory for the array
    *addr = (int *)malloc(array_size * sizeof(int));
    if (*addr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    memcpy(*addr, arr, array_size * sizeof(int));
    return array_size;
}

void remove_dup_3(int **addr, int *size, int *arr, int array_size) {
    // Allocating new memory for the array
    *addr = (int *)malloc(array_size*sizeof(int));
    if (*addr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    memcpy(*addr, arr, array_size * sizeof(int));
    *size = array_size;
}

// Printing the arrays
void print_arr(int *arr, int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int main () {
    int sorted_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(sorted_array) / sizeof(int);
    int *new_array_1 = NULL, *new_array_2 = NULL, *new_array_3 = NULL;
    int new_size_1, new_size_2, new_size_3;

    // Apply methods
    new_array_1 = remove_dup_1(&new_size_1, sorted_array, size);
    new_size_2 = remove_dup_2(&new_array_2, sorted_array, size);
    remove_dup_3(&new_array_3, &new_size_3, sorted_array, size);

    // Printing all outcomes
    print_arr(new_array_1, new_size_1);
    print_arr(new_array_2, new_size_2);
    print_arr(new_array_3, new_size_3);

    // Freeing all allocated memory
    free(new_array_1);
    free(new_array_2);
    free(new_array_3);

    exit(EXIT_SUCCESS);
}