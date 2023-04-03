#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


void printFileProperties(char *input) {    

    struct stat info;
    char expression;

    if(stat(input, &info) != 0) {
        perror("stat() error");
        return;
    } 

    printf("File properties:\n n -> name of the file\n a -> access rights\n d -> file size;\n h -> number of hardlinks\n m -> time of last modification\n");
    printf("What do you want to see? operation; ");
    scanf("%c", &expression);
    switch (expression)
    {
    case 'n':
        printf("\nName of the file is: %s", input);
        printf("\n");
        break;
    
    case 'a':
         printf("\nFile access rights:");
            if(info.st_mode & R_OK)
                printf(" read");
            if(info.st_mode & W_OK)
                printf(" write");
            if(info.st_mode & X_OK)
                printf(" execute\n");
        break;

    case 'd':
        long int size_of_file;
        size_of_file = info.st_size;
        printf("\nThe size of the file: %ld  bytes",size_of_file);
        printf("\n");
        break;

    case 'h':
        printf("Number of hardlinks: %ld", info.st_nlink);
        printf("\n");
        break;

    case 'm':
        printf("The last modified on: %s", ctime(&info.st_mtime));
        printf("\n");
        break;

        default:
        printf("Invalid operant please try one from the provided list.");
        break;
    }



}




int main() {  

    

    char filename[100];
    printf("Enter the file name: ");
    fgets(filename, 100, stdin);

    // Remove the newline character from the end of the filename
    int i = 0;
    while (filename[i] != '\n') {
        i++;
    }
    filename[i] = '\0';

    printFileProperties(filename);
    return 0;



}