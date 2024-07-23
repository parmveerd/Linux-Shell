
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[20];

    fp = fopen("/etc/shells", "r");
    // if file cannot be opened
    if (fp == NULL) {
        printf("Error. Cannot open file.\n");
        return 1;
    }

    // needed to make sure we skip the first 2 rows of the file
    int count = 0;
    // count how many slashes are in each line
    int slash = 0;
    // array to store the shells
    char shells[128][50];
    // shell after removing its location
    char *token;
    // keep track of the count in the array
    int shell_items = 0;
    // length of each row
    int line_count;
    // acts as a boolean to check if shell already exists in array
    int duplicate = 0;

    // loop through each row
    while ((fgets(line, sizeof(line), fp)) != NULL) {
        // skip the first two rows in the file
        if (count > 1) {
            
            // loop to check how many / in each line
            line_count = strlen(line);
            for (int i = 0; i < line_count; i++) {
                if (line[i] == '/') {
                    slash++;
                }
            }
            
            // loop to remove the location to get just the shell and store in token
            if (slash > 0) {
                token = strtok(line, "/");
                for (int i = 0; i < slash-1; i++) {
                    token = strtok(NULL, "/");
                }
            }
    
            // loop through array to check for duplicates
            for (int i = 0; i < shell_items; i++) {
                if (strcmp(shells[i], token) == 0) {
                    // already exists in array so change bool to true
                    duplicate = 1;
                    break;
                }
            }
            
            // insert into array if not already in there and increase count of array
            if (duplicate == 0) {
                strcpy(shells[shell_items], token);
                shell_items++;
            }
            // reset duplicate and slash for the next iteration
            duplicate = 0;
            slash = 0;
        }
        // increase count of row
        count++;
    }

    // loop through array and print out all the shells without duplicates
    for (int j = 0; j < shell_items; j++) {
        printf("%s", shells[j]);
    }
    
    return 0;   
}