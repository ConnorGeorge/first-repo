#include <stdio.h>

void transpose(int a[][3], int b[][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            b[j][i] = a[i][j];
        }
    }
}

void printArray(int a[][2] ){
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n"); // start new line of output 
    }
}

int main() {
    int array[2][3] = {1, 2, 3, 4, 5, 6};
    int out[3][2];

    transpose(array, out);
    printArray(out);
}
