#include <stdio.h>
#include <string.h>

typedef struct {
    char name [20];
    char student_id [11]; // Assuming 10 digits.
    unsigned mark;
} student;

int main () {
    int number_of_students = 10, i;
    student students[10];

    char format_buffer[10];

    for (i = 0; i < number_of_students; i++) {
        snprintf(format_buffer, 10, "Student %d", i);
        strcpy(students[i].name, format_buffer);

        snprintf(format_buffer, 10, "2835721%d", i);
        strcpy(students[i].student_id, format_buffer);

        students[i].mark = 35 + (17 * (i + 13)) % 65;
    }
    
    for (i = 0; i < number_of_students; i++) {
        printf("-------------\n");
        printf("Student name: %s\n", students[i].name);
        printf("Student ID: %s\n", students[i].student_id);
        printf("Final mark: %u\n", students[i].mark);
    }
    printf("-------------\n");

    return 0;
}