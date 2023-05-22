#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

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

       while(readdir(directory)!=NULL) {
        char cpy[100];

        strcpy(cpy,entry->d_name);
        if ((strcmp(&cpy[strlen(entry->d_name)-1],"c")) && (strcmp(&cpy[strlen(entry->d_name)-2],".")))  {    
        
        Cfiles++;
   
        }
    }

    closedir(directory);
    printf("Number of C files is %d\n",Cfiles);
    break;
        
   }
}

int computeScore(int errors, int warnings) {
    int score;

    if (errors == 0 && warnings == 0) {
        score = 10;
    } else if (errors >= 1) {
        score = 1;
    } else if (errors == 0 && warnings >= 10) {
        score = 2;
    } else if (errors == 0 && warnings == 10) {
        score = 2 + 8 * ((10 - warnings) / 10);
    }
    return score;
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
                    
                    pid_t child1, child2;
                    int pfd[2];
                    char buff[1024];

                    if (pipe(pfd) == -1) {
                        perror("pipe");
                        exit(EXIT_FAILURE);
                    }

                        if (!(child1 = fork())) {
                        // First child process
                            printf("%s is a regular file\n", argv[i]);
                            printFileProperties(argv[i]);
                            printf("\n");
                            exit(0);
                        } else if ((child2 = fork()) < 0) {
                            // Error creating second child process
                            printf("An error has occurred when creating the child process\n");
                            } else if (child2 == 0) {
                                // Second child process
                                sleep(2);
                                close(pfd[0]); 

                                if (strstr(argv[i], ".c") != NULL) {
                        
                                if (dup2(pfd[1], STDOUT_FILENO) == -1) {
                                    perror("dup2");
                                    exit(EXIT_FAILURE);
                                }

                            char *args[] = {"bash", "test.sh", argv[i], "error.txt", NULL};
                            execv("/bin/bash", args);
                            exit(0);
                } else {
    
                    char *args[] = {"bash", "count_line.sh", argv[i], NULL};
                    execv("/bin/bash", args);
                    exit(0);
                }
            }
            // Parent process

            close(pfd[1]); // Close the writing end of the pipe

            int errors, warnings, score;

            FILE *fout = fopen("score.txt", "w");
                if (fout == NULL) {
                perror("fopen");
                exit(EXIT_FAILURE);
        }

                ssize_t num_read;
                while ((num_read = read(pfd[0], buff, sizeof(buff))) > 0) {
                sscanf(buff,"errors = %d", &errors);
                sscanf(buff,"warnings = %d", &warnings);
                score = computeScore(errors, warnings);
                fprintf(fout, "%s:%d\n", argv[i], score);
                printf("The score was printed in the file 'score.txt'\n");
    }

    fclose(fout);


    wait(&child1);
    printf("The PID of the child process 1 is: %d \n", (int)getpid());
    wait(&child2);
    printf("The PID of the child process 2 is: %d \n", (int)getpid());
}
    
        if (S_ISDIR(stats.st_mode)) {

                pid_t child3, child4;
                if (!(child3 = fork())) {
                    //first child
                    printf("%s is a directory", argv[i]);
                    printf("\n");
                    printDirProperties(argv[i]);
                    printf("\n");
                    exit(0);
                }   else if (!(child4 = fork())) {
                    // second child
                    execlp("touch","touch","Dir_name.txt",NULL);
                    exit(0);
                } else {
                    // parent
                    wait(&child3);
                    printf("The PID of the child process 3 is: %d \n", (int)getpid());
                    wait(&child4);
                    printf("The PID of the child process 4 is: %d \n", (int)getpid());
            }

    } 
        if (S_ISLNK(stats.st_mode)) {

            pid_t child5, child6;
                if (!(child5 = fork())) {
                // first child
                printf("%s is a symbolic link", argv[i]);
                printf("\n");
                printSymLinkProperties(argv[i]);
                printf("\n"); 
                exit(0);
                } else if (!(child6 = fork())) {
                    // second child
                    char *args[] = {"chmod", "750", argv[i], NULL};
                    execv("chmod", args);
                    exit(0);
                    
                    

                    exit(0);
                } else {
                    // parent
                    wait(&child5);
                    printf("The PID of the child process 5 is: %d \n", (int)getpid());
                    wait(&child6);
                    printf("The PID of the child process 6 is: %d \n", (int)getpid());
            }
                         
        }  


    }
    return 0;
}