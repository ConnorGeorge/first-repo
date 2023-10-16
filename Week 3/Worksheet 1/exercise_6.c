#include <stdio.h>

int main() {
    int input_value;

    while (1) {
        printf("Enter a number between 0 and 100 (exit: -1): ");
        scanf("%d", &input_value);

        if (input_value == -1) {
            break;
        }
        else if (input_value < 0) {
            printf("Number must be 0 or greater\n");
        }
        else if (input_value > 100) {
            printf("Number must be 100 or less\n");
        }
        else {
            printf("Valid number\n");
        }
    }
} 
