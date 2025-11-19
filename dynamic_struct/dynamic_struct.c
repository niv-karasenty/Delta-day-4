#include <stdio.h>
#include <stdlib.h>

#define SECONDS_MAX (60)
#define MINUTES_MAX (60)
#define HOURS_MAX (24)

// I chose to use unsigned int so we won't have to check if the numbers are non negative
typedef struct time_in_day {
    unsigned int seconds;
    unsigned int minutes;
    unsigned int hours;
};

int input_from_user(struct time_in_day *input) {
    unsigned int seconds, minutes, hours;
    printf("Enter time in day in the format hh:mm:ss: \n");
    if (scanf("%d:%d:%d", &hours, &minutes, &seconds) == 0) {
        return 1;
    }
    if (seconds < SECONDS_MAX && minutes < MINUTES_MAX && hours < HOURS_MAX) {
        input->seconds = seconds;
        input->minutes = minutes;
        input->hours = hours;
        return 0;
    }
    else {
        printf("Invalid input\n");
        return 2;
    }
}

// Using modulo to add times
void add_times(struct time_in_day *src1, struct time_in_day *src2, struct time_in_day *dst) {
    dst->seconds = (src1->seconds + src2->seconds) % SECONDS_MAX;
    dst->minutes = (src1->minutes + src2->minutes) % MINUTES_MAX;
    // Adjusting off set, the sum of the seconds cannot be more than 1:58 and same for the sum of the minutes
    if (src1->seconds + src2->seconds >= SECONDS_MAX) {
        dst->minutes = (dst->minutes ++) % MINUTES_MAX;
    }
    dst->hours = (src1->hours + src2->hours) % HOURS_MAX;
    if (src1->minutes + src2->minutes >= MINUTES_MAX) {
        dst->hours = (dst->hours ++) % HOURS_MAX;
        if (src1->hours + src2->hours + 1 >= HOURS_MAX) {
            printf("Moved on to the next day\n");
        }
    }
    else if (src1->hours + src2->hours >= HOURS_MAX) {
        printf("Moved on to the next day\n");
    }
}

int main() {
    // Starting by allocating memory for two pointers of the structures
    struct time_in_day *ptr1 = (struct time_in_day *) malloc(sizeof(struct time_in_day));
    if (ptr1 == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    struct time_in_day *ptr2 = (struct time_in_day *) malloc(sizeof(struct time_in_day));
    if (ptr2 == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Input from user
    if (input_from_user(ptr1)) {
        printf("input problem\n");
        exit(EXIT_FAILURE);
    }
    if (input_from_user(ptr2)) {
        printf("input problem\n");
        exit(EXIT_FAILURE);
    }

    // Creating the 3rd pointer and adding the times together
    struct time_in_day *ptr3 = (struct time_in_day *) malloc(sizeof(struct time_in_day));
    if (ptr3 == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Printing added time
    add_times(ptr1, ptr2, ptr3);
    printf("The time added is: %d:%d:%d", ptr3->hours, ptr3->minutes, ptr3->seconds);

    // Freeing all memory
    free(ptr1);
    free(ptr2);
    free(ptr3);

    exit(EXIT_SUCCESS);
}
