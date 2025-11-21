#include "shell.h"
#include "parser/parser.h"
#include "commands/fs_commands.h"
#include "commands/file_read_commands.h"
#include "commands/sys_commands.h"
#include "commands/proc_commands.h"
#include "commands/net_commands.h"
#include <string.h>

void shell_init(ShellState *state) {
    state->history_count = 0;
    state->alias_count = 0;
    state->env_count = 0;
    state->running = 1;
    
    printf("========================================\n");
    printf("  Welcome to My Shell v1.0\n");
    printf("  Type 'help' for available commands\n");
    printf("========================================\n\n");
}

void add_to_history(ShellState *state, const char *cmd) {
    if (state->history_count < MAX_HISTORY) {
        strncpy(state->history[state->history_count], cmd, MAX_INPUT_SIZE - 1);
        state->history_count++;
    } else {
        // Shift history
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            strcpy(state->history[i], state->history[i + 1]);
        }
        strncpy(state->history[MAX_HISTORY - 1], cmd, MAX_INPUT_SIZE - 1);
    }
}

void print_history(ShellState *state) {
    printf("Command History:\n");
    for (int i = 0; i < state->history_count; i++) {
        printf("%3d  %s\n", i + 1, state->history[i]);
    }
}

void add_alias(ShellState *state, const char *alias, const char *command) {
    if (state->alias_count < MAX_ALIASES) {
        strncpy(state->aliases[state->alias_count][0], alias, 127);
        strncpy(state->aliases[state->alias_count][1], command, 127);
        state->alias_count++;
        printf("Alias created: %s -> %s\n", alias, command);
    } else {
        printf("Maximum aliases reached\n");
    }
}

const char* resolve_alias(ShellState *state, const char *cmd) {
    for (int i = 0; i < state->alias_count; i++) {
        if (strcmp(state->aliases[i][0], cmd) == 0) {
            return state->aliases[i][1];
        }
    }
    return cmd;
}

void print_aliases(ShellState *state) {
    if (state->alias_count == 0) {
        printf("No aliases defined\n");
        return;
    }
    
    printf("Defined Aliases:\n");
    for (int i = 0; i < state->alias_count; i++) {
        printf("  %s -> %s\n", state->aliases[i][0], state->aliases[i][1]);
    }
}

void add_env_var(ShellState *state, const char *key, const char *value) {
    // Check if variable exists
    for (int i = 0; i < state->env_count; i++) {
        if (strcmp(state->env_vars[i][0], key) == 0) {
            strncpy(state->env_vars[i][1], value, 255);
            printf("Updated: %s=%s\n", key, value);
            return;
        }
    }
    
    // Add new variable
    if (state->env_count < MAX_ENV_VARS) {
        strncpy(state->env_vars[state->env_count][0], key, 255);
        strncpy(state->env_vars[state->env_count][1], value, 255);
        state->env_count++;
        printf("Set: %s=%s\n", key, value);
    } else {
        printf("Maximum environment variables reached\n");
    }
}

const char* get_env_var(ShellState *state, const char *key) {
    for (int i = 0; i < state->env_count; i++) {
        if (strcmp(state->env_vars[i][0], key) == 0) {
            return state->env_vars[i][1];
        }
    }
    return NULL;
}

void print_env_vars(ShellState *state) {
    if (state->env_count == 0) {
        printf("No environment variables set\n");
        return;
    }
    
    printf("Environment Variables:\n");
    for (int i = 0; i < state->env_count; i++) {
        printf("  %s=%s\n", state->env_vars[i][0], state->env_vars[i][1]);
    }
}

static void execute_command(ShellState *state, ParsedCommand *cmd) {
    if (cmd->argc == 0) return;
    
    const char *command = resolve_alias(state, cmd->args[0]);
    
    // File system commands
    if (strcmp(command, "mkdir") == 0) {
        cmd_mkdir(cmd->argc, cmd->args);
    } else if (strcmp(command, "rmdir") == 0) {
        cmd_rmdir(cmd->argc, cmd->args);
    } else if (strcmp(command, "rm") == 0) {
        cmd_rm(cmd->argc, cmd->args);
    } else if (strcmp(command, "touch") == 0) {
        cmd_touch(cmd->argc, cmd->args);
    } else if (strcmp(command, "ls") == 0) {
        cmd_ls(cmd->argc, cmd->args);
    } else if (strcmp(command, "cd") == 0) {
        cmd_cd(cmd->argc, cmd->args);
    } else if (strcmp(command, "pwd") == 0) {
        cmd_pwd(cmd->argc, cmd->args);
    } else if (strcmp(command, "cp") == 0) {
        cmd_cp(cmd->argc, cmd->args);
    } else if (strcmp(command, "mv") == 0) {
        cmd_mv(cmd->argc, cmd->args);
    } else if (strcmp(command, "tree") == 0) {
        cmd_tree(cmd->argc, cmd->args);
    }
    // File read commands
    else if (strcmp(command, "cat") == 0) {
        cmd_cat(cmd->argc, cmd->args);
    } else if (strcmp(command, "echo") == 0) {
        cmd_echo(cmd->argc, cmd->args);
    }
    // System commands
    else if (strcmp(command, "clear") == 0) {
        cmd_clear(cmd->argc, cmd->args);
    } else if (strcmp(command, "exit") == 0) {
        cmd_exit(cmd->argc, cmd->args, state);
    } else if (strcmp(command, "sleep") == 0) {
        cmd_sleep(cmd->argc, cmd->args);
    } else if (strcmp(command, "time") == 0) {
        cmd_time(cmd->argc, cmd->args);
    } else if (strcmp(command, "help") == 0) {
        cmd_help(cmd->argc, cmd->args);
    }
    // Shell commands
    else if (strcmp(command, "history") == 0) {
        print_history(state);
    } else if (strcmp(command, "alias") == 0) {
        if (cmd->argc < 3) {
            print_aliases(state);
        } else {
            add_alias(state, cmd->args[1], cmd->args[2]);
        }
    } else if (strcmp(command, "set") == 0) {
        if (cmd->argc < 2) {
            print_env_vars(state);
        } else if (cmd->argc < 3) {
            const char *val = get_env_var(state, cmd->args[1]);
            if (val) {
                printf("%s=%s\n", cmd->args[1], val);
            } else {
                printf("Variable not set: %s\n", cmd->args[1]);
            }
        } else {
            add_env_var(state, cmd->args[1], cmd->args[2]);
        }
    } else if (strcmp(command, "export") == 0) {
        if (cmd->argc < 2) {
            printf("Usage: export KEY=VALUE\n");
        } else {
            char *eq = strchr(cmd->args[1], '=');
            if (eq) {
                *eq = '\0';
                add_env_var(state, cmd->args[1], eq + 1);
            } else {
                printf("Invalid format. Use: export KEY=VALUE\n");
            }
        }
    }
    // Process commands
    else if (strcmp(command, "ps") == 0) {
        cmd_ps(cmd->argc, cmd->args);
    } else if (strcmp(command, "kill") == 0) {
        cmd_kill(cmd->argc, cmd->args);
    } else if (strcmp(command, "run") == 0) {
        cmd_run(cmd->argc, cmd->args);
    }
    // Network commands
    else if (strcmp(command, "ping") == 0) {
        cmd_ping(cmd->argc, cmd->args);
    } else if (strcmp(command, "ifconfig") == 0 || strcmp(command, "ipconfig") == 0) {
        cmd_ifconfig(cmd->argc, cmd->args);
    } else if (strcmp(command, "curl") == 0) {
        cmd_curl(cmd->argc, cmd->args);
    }
    // Unknown command
    else {
        printf("Unknown command: %s\n", command);
        printf("Type 'help' for available commands\n");
    }
}

void shell_run(ShellState *state) {
    char input[MAX_INPUT_SIZE];
    char cwd[MAX_PATH_LEN];
    
    while (state->running) {
        // Print prompt with current directory
        if (getcwd_wrapper(cwd, sizeof(cwd))) {
            printf("\n%s> ", cwd);
        } else {
            printf("\nshell> ");
        }
        
        fflush(stdout);
        
        // Read input
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }
        
        // Add to history
        add_to_history(state, input);
        
        // Parse and execute
        ParsedCommand cmd = parse_command(input);
        execute_command(state, &cmd);
        free_parsed_command(&cmd);
    }
}

void shell_cleanup(ShellState *state) {
    printf("\nShell terminated.\n");
}