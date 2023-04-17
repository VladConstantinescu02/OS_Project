#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


void printFileProperties(char *input) {    
    struct stat info;
    char expression;

    if (lstat(input, &info) != 0) {
        perror("stat");
        return;
    }

    printf("File properties:\n n -> name of the file\n a -> access rights\n d -> file size;\n h -> number of hardlinks\n m -> time of last modification\n l -> create symbolic link\n");
    printf("What do you want to see? operation; ");
    scanf(" %c", &expression);
    switch (expression)
    {
    case 'n':
        printf("\nName of the file is: %s", input);
        printf("\n");
        break;
    
    case 'a':
         printf("\nFile access rights:\n");
             printf("For owner:\n");
            if(info.st_mode & S_IRUSR)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(info.st_mode & S_IWUSR)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(info.st_mode & S_IXUSR)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
        printf("For group:\n");
            if(info.st_mode & S_IRGRP)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(info.st_mode & S_IWGRP)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(info.st_mode & S_IXGRP)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
        printf("For other:\n");
            if(info.st_mode & S_IROTH)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(info.st_mode & S_IWOTH)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(info.st_mode & S_IXOTH)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
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

    case 'l':
        char link_name[100];
        printf("Please provide a link name: ");
        scanf("%s", link_name);
        if(symlink(input, link_name) < 0) {
            printf("error: Link was not created\n");
            break;
        } else {
            printf("Symbolic link was succesfuly created\n");
            printf("Link name: %s -> file name %s",link_name, input);
            printf("\n");
            break;
        }
        break;

        default:
        printf("Invalid operant please try one from the provided list.");
        break;
    }

}

void printSymLinkProperties(char *link) {    
    struct stat info;
    char expression;

    if (lstat(link, &info) != 0) {
        perror("stat");
        return;
    }

   printf("File properties:\n n -> link name\n a -> access rights\n d -> size of the link;\n t -> size of the target\n l -> delete link\n");
   printf("What do you want to see? operation; ");
   scanf(" %c", &expression);
   switch (expression)
    {   
        case 'n':
        printf("Name of the link is %s", link);
        printf("\n");
        break;

        case 'a':
        printf("\nLink access rights:\n");
        printf("For owner:\n");
            if(info.st_mode & S_IRUSR)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(info.st_mode & S_IWUSR)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(info.st_mode & S_IXUSR)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
        printf("For group:\n");
            if(info.st_mode & S_IRGRP)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(info.st_mode & S_IWGRP)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(info.st_mode & S_IXGRP)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
        printf("For other:\n");
            if(info.st_mode & S_IROTH)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(info.st_mode & S_IWOTH)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(info.st_mode & S_IXOTH)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
        break;

        case 'd':
        printf("\nThe size of the link(length of the pathname): %ld ",info.st_size);
        printf("\n");
        break;

        case 't':
        struct stat target;
        if(stat(link, &target) < 0) {
            printf("error Unable to locate target");
            
        } else {
        printf("The size of the tahget is: %lld", (long long)target.st_size);
        }
        printf("\n");
        break;

        case 'l':
        if( unlink(link) < 0) {
            printf("error Link could not be deleted");
        } else {
            printf("SymLink was deleted");
        }
        break;
        
        default:
        printf("Invalid operant please try one from the provided list.");
        break;
    }

        

}



int main(int argc, char *argv[]) {   
    struct stat stats;
     if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    } 

    for(int i=0; i < argc; i++)
    if (lstat(argv[i], &stats) != 0) {
        perror("stat");
        return 1;
    } else if (S_ISREG(stats.st_mode)) {  
        printf("%s is a regular file", argv[i]);
        printf("\n");
        printFileProperties(argv[i]);
        printf("\n");
    }   else if (S_ISLNK(stats.st_mode)) {
        printf("%s is a symbolic link", argv[i]);
        printf("\n");
        printSymLinkProperties(argv[i]);
        printf("\n");
    }   else if (S_ISDIR(stats.st_mode)) {
        printf("%s is a directory link", argv[i]);
        printf("\n");
    }

    return 0;
}