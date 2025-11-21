#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



//parse input into command and argument
//tokenizes command
ParsedCommand parse_command(char *input)
{
    ParsedCommand cmd;
    cmd.argc = 0;

    char *token = strtok(input, " \t\n\r");
    while (token != NULL && cmd.argc < MAX_ARGS)
    {
        cmd.args[cmd.argc] = strdup(token);
        cmd.argc++;
        token = strtok(NULL, " \t\n\r");
    }
    cmd.args[cmd.argc] = NULL;

    return cmd;
}

void free_parsed_command(ParsedCommand *cmd)
{
    for(int i = 0; i < cmd->argc; i++)
    {
        free(cmd->args[i]);
    }
}