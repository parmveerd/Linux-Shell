
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length 256

int main () {
    // get input for username
    char username[max_length];
    printf("Enter username: ");
    fgets(username, max_length, stdin);

    // remove newline character so we can put username in command string
    username[strcspn(username, "\n")] = '\0';

    // get the user ID and store it inside command
    char command[max_length + 18];
    // redirect any error message to /dev/null
    snprintf(command, sizeof(command), "id -u %s 2>/dev/null", username);

    // open command
    FILE *fp = popen(command, "r");
    // in case command does not open
    if (fp == NULL) {
        printf("Error. Cannot open file.\n");
        return 1;
    }

    char uid[max_length];
    // check the output stored in command
    if (fgets(uid, max_length, fp) != NULL) {
        // username exists, so output the user ID
        printf("%s", uid);
    } 
    else {
        // the output is null so this user does not exist
        printf("no such user found\n");
    }
    
    pclose(fp);
    
    return 0;
}