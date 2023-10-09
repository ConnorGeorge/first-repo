#include <stdio.h>

int main() {
    float width;
    float height;
    float area;

    printf("Enter width: ");
    scanf("%f", &width);

    printf("Enter height: ");
    scanf("%f", &height);

    area = width * height;

    printf("Area is %f\n", area);
}
