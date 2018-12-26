#include <stdio.h>
#include <stdlib.h>

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

    while (fscanf(ifp, "%s %d", name, &score) == 2) {
        // Add to the student and score cumulative counters
        students++;
        total += score;

        // Re-calculate the running average
        avg = total / students;

        // Print student name
        fprintf(ofp, ": %s \n", name);
    }

    fprintf(ofp, "Statistics: \n");

    fprintf(ofp, "Average grade: %d%%\n", (int) avg);

    fclose(ifp);
    fclose(ofp);

    return 0;
}

