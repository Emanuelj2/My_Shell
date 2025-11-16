#include "file_read_commands.h"
#include <stdio.h>
#include <string.h>


void cmd_cat(int argc, char **argv)
{
    //check if there are enough args
    if(argc < 2)
    {
        printf("Usage: cat <file>\n");
        return;
    }

    FILE *fp = fopen(argv[1], "r");
    if(!fp)
    {
        printf("cat fail!");
        return;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), fp))
    {
        printf("%s", buffer);
    }
    fclose(fp);

}

void cmd_echo(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("\n");
        return;
    }

    //check if redirecting to file
    int redirect_index = -1;
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], ">") == 0)
        {
            redirect_index = i;
            break;
        }
    }

    /* 
    echo hello > out.txt
        argv = ["echo", "hello", ">", "out.txt"]
                            ↑
                    redirect_index = 2

    */

    if(redirect_index > 0 && redirect_index < argc -1)
    {
        //redirect to file
        FILE *fp = fopen(argv[redirect_index + 1], "w");
        if(!fp)
        {
            printf("echo fail");
            return;
        }

        for(int i = 1; i < redirect_index; i++)
        {
            fprintf(fp, "%s", argv[i]);
            if(i < redirect_index -1) fprintf(fp, " ");
        }
        fprintf(fp, "\n");
        fclose(fp);
        printf("Write to %s\n", argv[redirect_index + 1]);
    }
    else
    {
        //print to stdout
        for(int i = 1; i < argc; i++)
        {
            printf("%s", argv[i]);
            if(i < argc -1) printf(" ");
        }
        printf("\n");
    }
}