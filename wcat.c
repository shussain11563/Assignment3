#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include<fcntl.h>

int isDir(char *filename)
{
    struct stat meta_data;
    int status = stat(filename, &meta_data);
    if(status==-1)
    {
        perror("File Does Not Exist"); 
        return -1;
    }

    if(S_ISDIR(meta_data.st_mode))
    {
        return 1;
    }

    return 0;
}




int main(int argc, char **argv)
{
    //pid_t id = fork();
    int EXIT_STATUS = EXIT_SUCCESS;
    int page_width = atoi(argv[1]);



    for(int i = 2; i < argc; i++)
    {
        
        if(isDir(argv[i])==1)
        {
            char* errorMessage = "Error: This is a directory!\n";
            write(2, errorMessage, strlen(errorMessage));
            EXIT_STATUS = EXIT_FAILURE;
            continue;
            
        }
        
        pid_t id = fork();
        if(id==0)
        {
            //puts("Child");
            execl("ww", "ww", argv[1], argv[i], NULL);
        }
        else
        {
            wait(NULL);
            //puts("Parent");
            //putchar('\n');
            putchar('\n');
        }
        //wait(NULL);

    }




    return EXIT_STATUS;
}

