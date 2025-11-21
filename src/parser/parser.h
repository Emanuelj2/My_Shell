#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64

typedef struct {
    char *args[MAX_ARGS + 1];  // +1 for NULL terminator
    int argc;
} ParsedCommand;

// Parse input into command and arguments
ParsedCommand parse_command(char *input);
void free_parsed_command(ParsedCommand *cmd);

#endif // PARSER_H