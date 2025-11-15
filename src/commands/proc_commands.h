#ifndef PROC_COMMANDS_H
#define PROC_COMMANDS_H

//function that lists running processes
void cmd_ps(int argc, char **argv);

void cmd_kill(int argc, char **argv);

void cmd_run(int argc, char **argv);

#endif

/*
int argc = 2;
char **argv = ["sleep", "10"];


argv[0] → "sleep" (the command name)
argv[1] → "10" (the first argument)

*/