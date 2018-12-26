#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    // Create references to input and output files
    FILE *ifp, *ofp;
    // Declare the mode we are using the printing with (read / write)
    char *mode = "r";
    // Note input and output filenames
    char inputFilename[] = "input.txt";
    char outputFilename[] = "output.txt";

    // Init (temp) variables to put file inputs into
    char name[9];  /* Name of student (max length of 8). One extra for nul char. */
    int score; /* score of student */

    // Init the dynamic average counting.
    double avg;
    short students;
    double total;
    double cumulative_deviations_squared = 0;

    // Open input file
    ifp = fopen(inputFilename, mode);
    // Verify input file
    if (ifp == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }

    // Open output file
    ofp = fopen(outputFilename, "w");
    // Verify output file
    if (ofp == NULL) {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }

    fprintf(ofp, "Students: \n");

    /*
     * Scan the file while the input count is valid (no issues with inputs
     */
    while (fscanf(ifp, "%s %d", name, &score) == 2) {
        // Add to the student and score cumulative counters
        students++;
        total += score;

        // Re-calculate a running average
        avg = total / students;

        // Print student name
        fprintf(ofp, ": %s \n", name);
    }

    ifp = fopen(inputFilename, mode);

    /*
     * Scan the file while the input count is valid (no issues with inputs
     */
    while (fscanf(ifp, "%s %d", name, &score) == 2) {
        // Get difference
        double diff = ((double) score) - avg;
        // Square it
        diff = diff * diff;
        // Add to sum
        cumulative_deviations_squared += diff;
    }

    double stdDev = sqrt(cumulative_deviations_squared / students);


    fprintf(ofp, "\nStatistics: \n");

    fprintf(ofp, "Average grade: %.1f%%\n", avg);
    fprintf(ofp, "Standard deviation: %.3f", stdDev);

    // Close input and output files
    fclose(ifp);
    fclose(ofp);

    return 0;
}

