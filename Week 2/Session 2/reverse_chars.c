#include <stdio.h>
#include <string.h>

int main() {
    char hello[] = "hello";
    int i;

    int length = strlen(hello);

    for (i = (length-1); i >= 0; i--) {
        printf("%c\n", hello[i]);
    }
}