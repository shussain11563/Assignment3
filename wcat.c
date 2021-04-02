#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int isDir(char *filename)
{
    struct stat meta_data;
    int status = stat(filename, meta_data);
    if(status==-1)
    {
        perror("File Does Not Exist");
    }

    if((meta_data.st_mode & S_IFMT)==S_IFDIR)
    {
        puts("dir");
    }
    else
    {
        puts("file");
    }
}




int main(int argc, char **argv)
{
    //pid_t id = fork();
    int page_width = atoi(argv[1]);
    
    int i = 2;
    while(i<argc)
    {
        //puts(argv[i]);

        pid_t id = fork();
        //execl("ww", "ww", argv[1], argv[i], NULL);
        if(id==0)
        {
            //puts("Child");
            execl("ww", "ww", argv[1], argv[i], NULL);
        }
        else
        {
            //puts("Parent");
            putchar('\n');
        }
        //putchar('\n');
        //d


        wait(NULL);


        i++;
    }


    return EXIT_SUCCESS;
}

