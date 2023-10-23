#include "utils.h"
#include <stdio.h>

int main() {
    FILE *file = open_file("data.txt", "w");
    fclose(file);
}
