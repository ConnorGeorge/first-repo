#include <stdio.h>

void reverseArray(int *array, int length) {
    int temp_int;
    for (int i = 0; i < length/2; i++) {
        temp_int = array;
        
        (array + length-1-i) = array + i;
        (array + i) = temp_int;
    }
}

int main() {
    int array[10];
    
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }

    reverseArray(array, 10);

    printf("%d", array[0]);
}
