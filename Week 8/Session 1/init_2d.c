#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int a[][3] ){
    for (size_t i = 0; i <= 1; ++i) {
        for (size_t j = 0; j <= 2; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n"); // start new line of output 
    }
}

void printArrayBig(int a[][4] ){
    for (size_t i = 0; i <= 2; ++i) {
        for (size_t j = 0; j <= 3; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n"); // start new line of output 
    }
}

void randomArray(int array[][4]) {
    srand(clock());

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            array[i][j] = rand() % 10;
        }
    }
}

int main() {
    int array1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("Values in array1 by row are:\n");
    printArray(array1);

    int array2[2][3] = {1, 2, 3, 4, 5};
    printf("Values in array2 by row are:\n");
    printArray(array2);

    int array3[2][3] = {{1, 2}, {4}};
    printf("Values in array3 by row are:\n");
    printArray(array3);

    printf("Values in random array by row are:\n");
    int rand[3][4];
    randomArray(rand);
    printArrayBig(rand);
}