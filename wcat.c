#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include<fcntl.h>

#ifndef WWPATH
#define WWPATH "ww"
#endif

int isDir(char *filename)
{
    struct stat meta_data;
    int status = stat(filename, &meta_data);
    if(status==-1)
    {
        //perror("File Does Not Exist"); 
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

        int fd[2];
        int pipeStatus = pipe(fd);
        if(pipeStatus==-1)
        {
            EXIT_STATUS = EXIT_FAILURE;
            return EXIT_STATUS;
        }   

        pid_t id = fork();
        if(id==-1)
        {
            EXIT_STATUS = EXIT_FAILURE;
            return EXIT_STATUS;
        }   

        if(id==0)
        {
            close(fd[0]);
            int dupStatus = dup2(fd[1],STDOUT_FILENO); 
            if(dupStatus ==-1)
            {
                EXIT_STATUS = EXIT_FAILURE;
                return EXIT_STATUS;
            }   
            
            close(fd[1]);
            int execStatus = execl(WWPATH, WWPATH, argv[1], argv[i], NULL);
            if(execStatus=-1)
            {
                EXIT_STATUS = EXIT_FAILURE;
                return EXIT_STATUS;
            }
        }
        else
        {
            close(fd[1]);
            
            int wstatus;
            int waitStatus = wait(&wstatus);
            if(waitStatus==-1)
            {
                EXIT_STATUS = EXIT_FAILURE;
                return EXIT_STATUS;
            }
            
            if(WIFEXITED(wstatus))
            {
                if(WEXITSTATUS(wstatus)==EXIT_FAILURE)
                {
                    EXIT_STATUS = EXIT_FAILURE;
                }
            }

            size_t BUFSIZE = 256;
            char* buf[BUFSIZE];
            int bytes = 0;
            while((bytes = read(fd[0], buf, BUFSIZE)) > 0)
            {
                write(STDOUT_FILENO, buf, bytes);
                if(bytes!=BUFSIZE && (i!=(argc-1)))
                {
                    putchar('\n');
                }
            }
            close(fd[0]);
        }

    }

    return EXIT_STATUS;
}

