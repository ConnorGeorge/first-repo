#include <stdio.h>

int main() {
    int a, b, c;

    printf("Enter number: ");
    scanf("%d", &a);

    printf("Enter number: ");
    scanf("%d", &b);

    c = a + b;

    printf("The sum of adding %d and %d is %d\n", a, b, c);
}