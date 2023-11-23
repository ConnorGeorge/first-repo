#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

FILE* open_file(char filename[], char mode[]) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Error: invalid file");
        exit(1);
    }
    return file;
}

int read_from_file(FILE *file, FitnessData *out) {
    // a couple extra chars in case there are large number of steps
    char line_buffer[25];
    int count = 0;

    while (fgets(line_buffer, 25, file) != NULL) {
        FitnessData *record = &out[count];
        char *date = record->date;
        char *time = record->time;
        date = NULL;
        time = NULL;
        record->steps = 0;

        tokeniseRecord(line_buffer, ',', record->date, record->time, &record->steps);
        if (out[count].date == NULL || out[count].time == NULL || out[count].steps == 0) {
            printf("Error: invalid file");
            exit(1);
        }

        count += 1;
    }

    return count;
}

void write_to_file(FILE *file, FitnessData *data) {

}

int main() {
    printf("Enter filename: ");
    char filename_input_buffer[30];
    scanf("%s", filename_input_buffer);

    FILE *csv_file = open_file(filename_input_buffer, "r");
    FitnessData all_data[1000];
    int count = read_from_file(csv_file, all_data);
    fclose(csv_file);

    FILE *tsv_file = open_file(, "w");
}