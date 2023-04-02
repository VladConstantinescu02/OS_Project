#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


void printFileProperties(char *filename) {    

    struct stat info;

    if(stat(filename, &info) != 0) {
        perror("stat() error");
        return;
    } else {  
    
    long int size_of_file;
    
    printf("\nFile access rights:");
    if(info.st_mode & R_OK)
        printf(" read");
    if(info.st_mode & W_OK)
        printf(" write");
    if(info.st_mode & X_OK)
        printf(" execute\n");

    size_of_file = info.st_size;
        printf("\nThe size of the file: %ld  bytes",size_of_file);
        printf("\n");

        printf("Number of hardlinks: %ld", info.st_nlink);
        printf("\n");
    }    
}

void createSymLink(char *file_name, char * link_name) {    

    int sym_link;

    sym_link =symlink(file_name,link_name);

    if(sym_link == 0)
    printf("Link was created succesfully");
    }


int main() {    

    printFileProperties("ex1.txt");

    createSymLink("ex1.txt", "ex1_link_s");

    return 0;
}