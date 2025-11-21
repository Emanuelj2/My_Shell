#include "shell.h"

int main(int argc, char *argv[])
{
    ShellState state;

    shell_init(&state);
    shell_run(&state);
    shell_cleanup(&state);

    return 0;
}