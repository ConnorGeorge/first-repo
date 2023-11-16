#include "utilities.h"

int main()
{
    // array of daily readings
    reading daily_readings[100];

    char line[BUFFER_SIZE];
    char filename[BUFFER_SIZE];

    // get filename from the user
    printf("Please enter the name of the data file: ");

    // these lines read in a line from the stdin (where the user types)
    // and then takes the actual string out of it
    // this removes any spaces or newlines.
    fgets(line, BUFFER_SIZE, stdin);
    sscanf(line, " %s ", filename);

    FILE* input = open_file(filename, "r");
    int counter = read_file(input, daily_readings);

    if (data_checker(daily_readings, counter) == 1) {
        printf("File format is invalid.\n");
        goto close_file;
    }

    while (1) {

        printf("\nA: View all your blood iron levels\n");                       // BRONZE
        printf("B: View your average blood iron level\n");                    // BRONZE
        printf("C: View your lowest blood iron level\n");                     // SILVER
        printf("D: View your highest blood iron level\n");                    // SILVER
        printf("E: View the blood iron levels for a specific month\n");       // SILVER/GOLD
        printf("F: See some additional statistics about your iron levels\n"); // GOLD - see readme.md
        printf("G: Generate a graph of your iron levels\n");                  // GOLD/PLATINUM - see readme.md
        printf("Q: Exit the program\n\n");
        printf("Enter option: ");

        // get the next character typed in and store in the 'choice'
        char choice = getchar();

        // this gets rid of the newline character which the user will enter
        // as otherwise this will stay in the stdin and be read next time
        while (getchar() != '\n');

        // switch statement to control the menu.
        switch (choice) {
        // this allows for either capital or lower case
        case 'A':
        case 'a':
            for (int i = 0; i < counter; i++) {
                print_reading(&daily_readings[i]);
            }
            break;

        case 'B':
        case 'b': ;
            float mean = find_mean(daily_readings, counter);
            printf("Your average blood iron was %.2f\n", mean);
            break;

        case 'C':
        case 'c': ;
            float lowest = find_lowest(daily_readings, counter);
            printf("Your lowest blood iron was %.2f\n", lowest);
            break;

        case 'D':
        case 'd': ;
            float highest = find_highest(daily_readings, counter);
            printf("Your highest blood iron was %.2f\n", highest);
            break;

        case 'E':
        case 'e':
            monthly_iron(daily_readings, counter);
            break;

        case 'F':
        case 'f': ;
            reading_statistics statistics;
            create_reading_statistics(daily_readings, counter, &statistics);

            printf(
                "Mean: %.2f\nMedian: %.2f\nRange: %.2f\nStandard Deviation: %.2f\n",
                statistics.mean, statistics.median, statistics.range, statistics.standard_deviation
            );

            break;

        case 'G':
        case 'g':
            return 0;
            break;

        case 'Q':
        case 'q':
            goto close_file;

        // if they type anything else:
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    close_file:
        fclose(input);
}