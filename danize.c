#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_COLUMN_LENGTH 100

void processCSV(const char* inputFilename, const char* outputFilename);

int main() {
    const char* inputFilename = "input.csv";
    const char* outputFilename = "newCSV.csv";

    processCSV(inputFilename, outputFilename);

    return 0;
}

void processCSV(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Failed to open input file: %s\n", inputFilename);
        return;
    }

    FILE* outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Failed to create output file: %s\n", outputFilename);
        fclose(inputFile);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int isFirstLine = 1; // Flag to identify the first line

    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Remove the trailing newline character
        line[strcspn(line, "\n")] = '\0';

        if (isFirstLine) {
            isFirstLine = 0;
            fprintf(outputFile, "%s\n", line);
            continue;
        }

        char* token = strtok(line, ",");
        int columnCount = 1;
        while (token != NULL) {
            if (columnCount == 16) {
                // Store the first 8 characters of the value from column 16 in column 9
                char* firstEightChars = strndup(token, 8);
                fprintf(outputFile, "%s,%s", token, firstEightChars);
                free(firstEightChars);
            } else if (columnCount == 10) {
                // Replace the value in column 10 with "Check"
                fprintf(outputFile, ",Check");
            } else if (columnCount == 24) {
                // Add the value 1014 after the twenty-fourth comma
                fprintf(outputFile, ",%s,1014", token);
            } else {
                // Copy the token as-is
                fprintf(outputFile, ",%s", token);
            }

            token = strtok(NULL, ",");
            columnCount++;
        }

        fprintf(outputFile, "\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("CSV processing completed successfully.\n");
}
