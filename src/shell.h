#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/platform.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define MAX_HISTORY 100
#define MAX_ALIASES 50
#define MAX_ENV_VARS 100


//shell state structuer
typedef struct
{
    char history[MAX_HISTORY][MAX_INPUT_SIZE];
    int history_count;
    char aliases[MAX_ALIASES][2][128];// [i][0] = alias, [i][1] = command
    int alias_count;
    char env_vars[MAX_ENV_VARS][2][256];
    int env_count;
    int running;
}ShellState;


//initialize shell and run
void shell_init(ShellState *state);
void shell_run(ShellState *state);
void shell_cleanup(ShellState *state);

//history mamagement
void add_to_history(ShellState *state, const char *cmd);
void print_history(ShellState *state);

//alias management
void add_alias(ShellState *state, const char *alias, const char *command);
const char* resolve_alias(ShellState *state, const char *cmd);
void print_aliases(ShellState *state);

//environment variable management
void add_env_var(ShellState *state, const char *key, const char *value);
const char* get_env_var(ShellState *state, const char *key);
void print_env_vars(ShellState *state);

#endif