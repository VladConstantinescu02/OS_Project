#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
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
    switch (expression) {
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
        printf("The size of the target is: %lld", (long long)target.st_size);
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

void printDirProperties(char *dirname) {
       char expression;

    int Cfiles = 0;

    DIR *directory;
    struct dirent *entry;

    struct stat dirstat;

    if (stat(dirname, &dirstat) != 0) {
        perror("stat");
        return;
    }

    

    printf("File properties:\n n -> directory name\n a -> access rights\n d -> size of the directory;\n c -> number of c files\n");
    printf("What do you want to see? operation; ");
    scanf(" %c", &expression);
   
   switch (expression) {

   case 'n':
        printf("\nName of the diectory is: %s", dirname);
        printf("\n");
   break;

   case 'd':
        if(S_ISDIR(dirstat.st_mode)) {
        printf("Size of directory is %lld in bytes", (long long)dirstat.st_size);
        printf("\n");
    }
   break;

   case 'a':
        printf("\nDirectory access rights:\n");
        printf("For owner:\n");
            if(dirstat.st_mode & S_IRUSR)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(dirstat.st_mode & S_IWUSR)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(dirstat.st_mode & S_IXUSR)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
                printf("For group:\n");
            if(dirstat.st_mode & S_IRGRP)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(dirstat.st_mode & S_IWGRP)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(dirstat.st_mode & S_IXGRP)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");
                printf("For other:\n");
            if(dirstat.st_mode & S_IROTH)
                printf("Read -> yes");
                else
                printf("Read -> no");
                printf("\n");
            if(dirstat.st_mode & S_IWOTH)
                printf("Write -> yes");
                else
                printf("Write -> no");
                printf("\n");
            if(dirstat.st_mode & S_IXOTH)
                printf("Execute -> yes");
                else
                printf("Execute -> no");
                printf("\n");

   break;

   case 'c':
   directory = opendir(dirname);

    if(directory == NULL) {
            printf("error Unable to read directory\n");
            return;
    } else {
        printf("Directory is opened!\n");
        return;
    }

       while( (entry=readdir(directory)) && (readdir(directory)!=NULL) )
    {
        char cpy[100];

        strcpy(cpy,entry->d_name);
        if ((strcmp(&cpy[strlen(entry->d_name)-1],"c")) && (strcmp(&cpy[strlen(entry->d_name)-2],".")))      
        
        Cfiles++;
    }
    printf("Number of C files is %d\n",Cfiles);
    closedir(directory);
    break;
        
   }
}



int main(int argc, char *argv[]) { 
    

    struct stat stats;
     if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    } 

    for(int i=1; i < argc; i++)
    if (lstat(argv[i], &stats) != 0) {
        perror("stat");
        return 1;
    } else {

        if (S_ISREG(stats.st_mode)) {  
        
        pid_t cpid1;
        cpid1 = fork();
        if (cpid1 < 0) {
        printf("error : Failed to create second child process");
        exit(1);
        }
        if(cpid1 == 0)  { // child process
        printf("%s is a regular file", argv[i]);
        printf("\n");
        printFileProperties(argv[i]);
        printf("\n");
        }

        pid_t cpid2;
        if(strlen(argv[i])-1 == 'c' && strlen(argv[i])-2 == '.') {
        cpid2 = fork();
        }
        if (cpid2 < 0) {
        printf("error : Failed to create second child process");
        exit(1);
        }
        if (cpid2 == 0) { // child process
            printf("Is a c file\n");
        }

            wait(0);
            wait(0);


    }   
        if (S_ISLNK(stats.st_mode)) {
        printf("%s is a symbolic link", argv[i]);
        printf("\n");
        printSymLinkProperties(argv[i]);
        printf("\n"); 

    }   
        if (S_ISDIR(stats.st_mode)) {

        pid_t cpid3;
        cpid3 = fork();
        if (cpid3 < 0) {
        printf("error : Failed to create second child process");
        exit(1);
        }

        if(cpid3 == 0)  { // child process
        printf("%s is a directory link\n", argv[i]);
        printDirProperties(argv[i]);
        printf("\n");
        } 

        wait(0);

        }
    
    }

    return 0;
}