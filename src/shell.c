#include "shell.h"
#include "parser/parser.h"
#include "commands/fs_commands.h"
#include "commands/file_read_commands.h"
#include "commands/sys_commands.h"
#include "commands/proc_commands.h"
#include "commands/net_commands.h"
#include <string.h>


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
