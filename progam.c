#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

int main() {
    int number = 0 ;
    scanf("%d", &number);
    pid_t child1, child2;
    child1 = fork();
    if (child1 < 0) {
        // Fork failed child1
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (child1 == 0) {
        // first child
        printf("\tChild 1\n");

        exit(0);
    } else if(number % 2 == 0){
            // second child
            child2 = fork();
            if (child2 < 0)
            {   // Fork failed child2
                fprintf(stderr, "Fork failed\n");
                return 1;
                
            } else if(child2 == 0) { 
                if(number % 2 == 0) 
                printf("\tIs even\n");
                exit(0);
            }
        exit(0);
            
    } else {
        // parent

        wait(&child1);
        wait(&child2);
    }

    return 0;
}