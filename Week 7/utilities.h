#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// declaring this value so I can use it in different places
#define BUFFER_SIZE 100

/**
 * @brief Struct to hold each daily reading, contains the date as a string
 *        and the bloodIron as a floating point number.
 *
 */
typedef struct
{
    char date[20];
    float bloodIron;
} reading;

typedef struct
{
    float range;
    float standard_deviation;
    float median;
    float mean;
} reading_statistics;

/**
 * @brief Adapted version of the tokeniseRecord function which you should now be familiar with - this one is adapted for this data file
 *        as it has fewer outputs and gives you the bloodIron as a float
 *
 * @param input the line of the file to be split
 * @param delimiter what character it should split on
 * @param date the place where the date will be stored
 * @param bloodIron the place where the bloodIron will be stored.
 */
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, float *bloodIron)
{
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL)
    {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        // turns the blood iron into a float - similar to atoi().
        // we have to tell C that bloodIron is a pointer so it stores it.
        *bloodIron = atof(token);
    }

    // Free the duplicated string
    free(inputCopy);
}

// SUGGESTED FUNCTIONS

void print_reading(reading* data) {
    printf("%s - Blood iron: %.1f\n", data->date, data->bloodIron);
}

/**
 * @brief Opens the file in the correct mode
 *
 * @param filename the name of the file to open
 * @param mode the mode (r/w/a/r+/w+/a+)
 * @return FILE* The file object to store the opened file in.
 */
FILE *open_file(char *filename, char *mode)
{
    FILE *input = fopen(filename, "r");
    if (!input)
    {
        printf("Error: File could not be opened\n");
        exit(1);
    }
    return input;
}

/**
 * @brief Reads the data from the input file into an array of structs
 *
 * @param inputFile the open file object
 * @param dataArray the array of readings
 * @return int Returns the number of readings from the file
 */
int read_file(FILE *inputFile, reading *dataArray)
{
    char line[BUFFER_SIZE];
    if (!inputFile) {
        printf("Error: File could not be opened\n");
        exit(1);
    }

    int counter = 0;
    while (fgets(line, BUFFER_SIZE, inputFile)) {
        // split up the line and store it in the right place
        // using the & operator to pass in a pointer to the bloodIron so it stores it
        tokeniseRecord(line, ",", dataArray[counter].date, &dataArray[counter].bloodIron);
        counter++;
    }

    return counter;
}

/**
 * @brief Checks that there was data for each part of each reading in the file
 *
 * @param dataArray The array of data from the file
 * @param numReadings The number of readings in the array
 * @return int Return 0 if there are no errors, 1 if you find an error.
 */
int data_checker(reading *dataArray, int numReadings)
{
    for (int i = 0; i < numReadings; i++) {
        reading current_reading = dataArray[i];
        if (current_reading.bloodIron == 0) {
            return 1;
        }
        if (current_reading.date == "") {
            return 1;
        }
    }
    return 0;
}


/**
 * @brief Calculates and returns the mean of the readings in the array
 * 
 * @param dataArray The array of data from the file
 * @param numReadings The number of readings in the array
 * @return float The mean of the readings.
 */
float find_mean(reading* dataArray, int numReadings)
{
    float mean = 0;

    for (int i = 0; i < numReadings; i++) {
        mean += dataArray[i].bloodIron;
    }
    mean /= numReadings;

    return mean;
}

/**
 * @brief Finds and returns the highest blood iron reading
 * 
 * @param dataArray The array of data from the file
 * @param numReadings The number of readings in the array
 * @return float The highest blood iron reading
 */
float find_highest(reading* dataArray, int numReadings)
{
    float maximum = __FLT_MIN__;
    float current_blood_iron;
    
    for (int i = 0; i < numReadings; i++) {
        current_blood_iron = dataArray[i].bloodIron;
        if (current_blood_iron > maximum) {
            maximum = current_blood_iron;
        }
    }

    return maximum;
}

/**
 * @brief Finds and returns the lowest blood iron reading
 * 
 * @param dataArray The array of data from the file
 * @param numReadings The number of readings in the array
 * @return float The lowest blood iron reading
 */
float find_lowest(reading* dataArray, int numReadings)
{
    float minimum = INFINITY;
    float current_blood_iron;
    
    for (int i = 0; i < numReadings; i++) {
        current_blood_iron = dataArray[i].bloodIron;
        if (current_blood_iron < minimum) {
            minimum = current_blood_iron;
        }
    }

    return minimum;
}

int cmpfunc (const void *a, const void *b) {
    reading a_f = *(reading*)a;
    reading b_f = *(reading*)b;
    return (a_f.bloodIron > b_f.bloodIron) - (a_f.bloodIron < b_f.bloodIron);
}

void create_reading_statistics(reading *dataArray, int numReadings, reading_statistics *out) {
    float mean = find_mean(dataArray, numReadings);
    (*out).mean = mean;

    float highest = find_highest(dataArray, numReadings);
    float lowest = find_lowest(dataArray, numReadings);
    (*out).range = highest - lowest;

    float mean_squares = 0.0;
    for (int i = 0; i < numReadings; i++) {
        mean_squares += pow(dataArray[i].bloodIron, 2);
    }
    mean_squares /= numReadings;
    (*out).standard_deviation = mean_squares - pow(mean, 2);

    reading sortedArray[BUFFER_SIZE];
    memcpy(sortedArray, dataArray, BUFFER_SIZE*sizeof(reading));
    qsort(sortedArray, numReadings, sizeof(reading), cmpfunc);
    (*out).median = sortedArray[numReadings / 2].bloodIron;
}

/**
 * @brief Ask the user for the month to find, and then print out all readings containing that month.
 * 
 * @param dataArray The array of data from the file
 * @param numReadings The number of readings in the array
 */
void monthly_iron(reading* dataArray, int numReadings)
{
    char line[BUFFER_SIZE];
    char month[BUFFER_SIZE];
    printf("Enter month: ");
    fgets(line, BUFFER_SIZE, stdin);
    sscanf(line, " %s ", month);

    char* s = &month[0];
    while (*s) {
        *s = toupper((unsigned char) *s);
        s++;
    }

    int found = 0;
    for (int i = 0; i < numReadings; i++) {
        if (strstr(dataArray[i].date, month) != NULL) {
            print_reading(&dataArray[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("None found\n");
    }
}