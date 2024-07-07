#include "philo.h"


#include <stdio.h>
#include <stdlib.h>

void print_eror(char *str) {
    printf("%s", str);
    exit(1);
}

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        print_eror("malloc error\n");
    }
    return ptr;
}

int main() {
    int *numbers;
    size_t num_count = 10;

    // Allocate memory for an array of integers using safe_malloc
    numbers = (int *)safe_malloc(num_count * sizeof(int));

    // Initialize and print the array
    for (size_t i = 0; i < num_count; i++) {
        numbers[i] = i + (i * 2);
        printf("numbers[%zu] = %d\n", i, numbers[i]);
    }

    // Free the allocated memory
    free(numbers);

    return 0;
}
 