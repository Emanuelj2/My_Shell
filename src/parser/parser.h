#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64

//make a struct for the struct
typedef struct
{
    char args[MAX_ARGS];    //this contians the max chars or char args
    int argc;               //this contins the number of arg numbers

}ParsedCommand;

//parse input into command and argument
ParsedCommand parse_command(char *input);
void free_parsed_command(ParsedCommand *cmd);

#endif