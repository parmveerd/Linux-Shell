
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length 256

int main() {
    FILE *fp;
    char line[max_length];
    // number of files
    int count = 0;
    // total number of usage
    double total = 0.0;

    // open a txt file so we can write in it
    fp = fopen("partition_usage.txt", "w");
    // if cannot open txt file
    if (fp == NULL) {
        printf("Cannot open txt file.\n");
        return 1;
    }

    // run the df command
    FILE *output = popen("df -h", "r");
    // if command did not execute
    if (output == NULL) {
        printf("Cannot execute command.\n");
        fclose(fp);
        return 1;
    }

    // write each line from the command output to txt file
    while (fgets(line, sizeof(line), output)) {
        fprintf(fp, "%s", line);
    }

    // close both file and output
    fclose(fp);
    pclose(output);

    // open the txt file for reading now
    fp = fopen("partition_usage.txt", "r");
    // if txt file does not open
    if (fp == NULL) {
        printf("Cannot open txt file to read.\n");
        return 1;
    }

    // loop through each row in the file
    while (fgets(line, sizeof(line), fp)) {
        // skip the header line
        if (strstr(line, "Filesystem") != NULL) {
            continue;
        }

        char usage[8];
        // skip the first 4 columns and store use% as a string
        sscanf(line, "%*s %*s %*s %*s %s", usage);

        // remove the percent sign
        char *percent = strchr(usage, '%');
        if (percent != NULL) {
            *percent = '\0';
        }

        // change char to float so we can add it to the total
        double value = atof(usage);

        // add usage to total and increase number of files
        total += value;
        count++;
    }

    // close the txt file
    fclose(fp);

    // find the average partition usage
    double averageUsage = total / count;

    // print the average partition usage with only 2 decimal spots
    printf("%.2lf\n", averageUsage);

    return 0;
}
