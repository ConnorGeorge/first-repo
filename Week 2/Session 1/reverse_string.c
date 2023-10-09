#include <stdio.h>

int main() {
    char input_buffer[20];
    printf("Enter string: ");
    scanf("%s", input_buffer);

    int length;
    printf("Enter string length: ");
    scanf("%d", &length);

    char temp_char;
    for (int i = 0; i < length/2; i++) {
        temp_char = input_buffer[length-1-i];
        input_buffer[length-1-i] = input_buffer[i];
        input_buffer[i] = temp_char;
    }

    printf("Reversed: %s\n", input_buffer);
}
