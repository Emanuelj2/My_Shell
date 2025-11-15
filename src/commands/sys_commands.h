#ifndef SYS_COMMSNDS_H
#define SYS_COMMANDS_H

#include "../shell.h"

void cmd_clear(int argc, char **argv);
void cmd_exit(int argc, char **argv, ShellState *state);
void cmd_sleep(int argc, char **argv);
void cmd_time(int argc, char **argv);
void cmd_help(int argc, char **argv);

#endif

/*
These are standard C parameters used for command-line–style functions, just like main(int argc, char *argv[]).

argc
 -Stands for argument count
 -it tells you how many arguments were passed to the command.

argv
 -Stands for argument vector
 -It is an array of strings, where:
 -argv[0] = the command name (like "clear")
 -argv[1] = first argument
 -argv[2] = second argument
 -etc.
*/