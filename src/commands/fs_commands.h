#ifndef FS_COMMANDS_H
#define FS_COMMANDS_H

//file system commands
void cmd_mkdir(int argc, char**argv);
void cmd_rmdir(int argc, char **argv);
void cmd_rm(int argc, char **argv);
void cmd_touch(int argc, char **argv);
void cmd_ls(int argc, char **argv);
void cmd_cd(int argc, char **argv);
void cmd_pwd(int argc, char **argv);
void cmd_cp(int argc, char **argv);
void cmd_mv(int argc, char **argv);
void cmd_tree(int argc, char **argv);

#endif

//char ** is a list/array of strings
/*
argc = argument count
argv = vector of arguments

example:
argv = ["echo", "hello", ">", "out.txt"]

argc = 4

argv[0] = "echo"
argv[1] = "hello"
argv[2] = ">"
argv[3] = "out.txt"

*/