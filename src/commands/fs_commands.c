#include "fs_commands.h"
#include <../utils/platform.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void cmd_mkdir(int argc, char**argv)
{
    if(argc < 2)
    {
        printf("Usage: mkdir <dir>\n");
        return;
    }

    if(mkdir_wrapper(argv[1]) == 0)
    {
        printf("Directory created: %s\n", argv[1]);
    }
    else
    {
        perror("mkdir failed");
    }
}


void cmd_rmdir(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage: rmdir <dir>\n");
        return;
    }

    if(rmdir_wrapper(argv[1]) == 0)
    {
        printf("Directory removed: %s\n", argv[1]);
    }
    else
    {
        perror("rmdir failed");
    }
}
void cmd_rm(int argc, char **argv);
void cmd_touch(int argc, char **argv);
void cmd_ls(int argc, char **argv);
void cmd_cd(int argc, char **argv);
void cmd_pwd(int argc, char **argv);
void cmd_cp(int argc, char **argv);
void cmd_mv(int argc, char **argv);
void cmd_tree(int argc, char **argv);
