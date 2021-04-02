#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include<fcntl.h>

#include <ctype.h> //remove 

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
        pipe(fd);

        pid_t id = fork();
        if(id==0)
        {
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO); 
            close(fd[1]);
            execl("ww", "ww", argv[1], argv[i], NULL);
        }
        else
        {

            close(fd[1]);
            
            int wstatus;
            wait(&wstatus);
            
            if(WEXITSTATUS(wstatus)==EXIT_FAILURE)
            {
                EXIT_STATUS = EXIT_FAILURE;
            }
            

            size_t BUFSIZE = 5;
            char* buf[BUFSIZE];
            int bytes = 0;
            while((bytes = read(fd[0], buf, BUFSIZE)) > 0)
            {
                write(1, buf, bytes);
                if(bytes!=BUFSIZE)
                {
                    putchar('\n');
                }

            }

    
            close(fd[1]);
            close(fd[0]);

        }

    }

    return EXIT_STATUS;
}

